#include "sandbox.hpp"

#include <algorithm>
#include <iostream>
#include <random>

extern std::default_random_engine rng;

Sandbox::Sandbox(unsigned int width, unsigned int height)
    : size(IVec2(width, height)),
    image(width, height, BLACK),
    texture(image)
{
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);

    cells.reserve(width * height);
    grid.reserve(width * height);
    new_grid.reserve(width * height);
    indices.reserve(width * height);

    for (size_t i = 0; i < width * height; i++) {
        if (distribution(rng) < 0.1) {
            cells.emplace_back(Cell(CellDefinition::Sand));
        } else {
            cells.emplace_back(Cell(CellDefinition::Nothing));
        }

        grid.emplace_back(i);
        new_grid.emplace_back(i);
        indices.emplace_back(i);
    }

    update_texture();
}

IVec2 Sandbox::get_position(size_t index) const {
    return IVec2(index % size.x, index / size.x);
}

size_t Sandbox::get_index(IVec2 position) const {
    return position.y * size.x + position.x;
}

bool Sandbox::in_bounds(IVec2 position) const {
    return position.x >= 0 && position.y >= 0 && position.x < size.x && position.y < size.y;
}

bool Sandbox::can_move(IVec2 source, IVec2 target) const {
    if (!in_bounds(source) || !in_bounds(target)) return false;

    std::vector<IVec2> points;
    for (int y = source.y; y <= target.y; y++) {
        points.emplace_back(source.x, y);
    }

    for (IVec2 target : points) {
        std::cout << target.x << " " << target.y << std::endl;
        if (cells[new_grid[get_index(target)]].definition != CellDefinition::Nothing) return false;
    }

    return true;
}

void Sandbox::update() {
    std::swap(grid, new_grid);
    std::copy(grid.begin(), grid.end(), new_grid.begin());

    for (Cell& cell : cells) {
        cell.moved = false;
    }

    std::shuffle(indices.begin(), indices.end(), rng);
    for (size_t i : indices) {
        IVec2 source = get_position(i);
        Cell& source_cell = cells[grid[i]];

        if (source_cell.definition == CellDefinition::Nothing) continue;

        if (can_move(source, source + IVec2(0, 1))) {
            source_cell.velocity.y += 1;
            IVec2 target = source + IVec2(0, source_cell.velocity.y);
            if (can_move(source, target)) {
                std::swap(new_grid[get_index(source)], new_grid[get_index(target)]);
            }
        } else {
            source_cell.velocity.y = 0;
        }
    }

    update_texture();
}

void Sandbox::draw() const {
    DrawTexturePro(
        texture,
        raylib::Rectangle(0, 0, size.x, size.y),
        raylib::Rectangle(0, 0, GetScreenWidth(), GetScreenHeight()),
        raylib::Vector2(0.0f, 0.0f),
        0.0f,
        WHITE
    );
}

void Sandbox::update_texture() {
    raylib::Color* data = (raylib::Color*) image.GetData();
    for (size_t i = 0; i < size.x * size.y; i++) {
        data[i] = cells[new_grid[i]].get_properties().color;
    }

    UpdateTexture(texture, image.GetData());
}
