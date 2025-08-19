#pragma once

#include "cell.hpp"

#include "raylib-cpp.hpp"

class Sandbox {
public:
    Sandbox(unsigned int width, unsigned int height);

    IVec2 get_position(size_t index) const;
    size_t get_index(IVec2 position) const;
    bool in_bounds(IVec2 position) const;
    std::vector<IVec2> get_line_points(IVec2 source, IVec2 target) const;
    bool can_move(IVec2 source, IVec2 target) const;
    void update();
    void draw() const;

private:
    IVec2 size;
    std::vector<Cell> cells;
    std::vector<size_t> grid;
    std::vector<size_t> new_grid;
    std::vector<size_t> indices;
    raylib::Image image;
    raylib::Texture2D texture;

    void update_texture();
};
