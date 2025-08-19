#pragma once

#include "raylib-cpp.hpp"

#include <functional>
#include <memory>

class Sandbox;

struct IVec2 {
    int x;
    int y;

    template <typename T>
    IVec2(T x, T y) : x(x), y(y) {}

    IVec2 operator+(const IVec2& other) {
        return IVec2(this->x + other.x, this->y + other.y);
    }
};

enum class CellDefinition {
    Nothing,
    Sand,
    Water,
    Oil,
    Fire,
    Smoke,
};

enum class CellType {
    None   = 0b000,
    Powder = 0b001,
    Liquid = 0b011,
    Gas    = 0b110,
    Plasma = 0b110,
};

class ICellBehavior {
public:
    virtual ~ICellBehavior() = default;
    virtual void update(Sandbox& sandbox, IVec2 position) = 0;
};

class FireBehavior : public ICellBehavior {
public:
    void update(Sandbox& sandbox, IVec2 position);

private:
    unsigned int lifetime = 60;
};

struct CellProperties {
    CellType type;
    float density;
    raylib::Color color;
    std::function<std::unique_ptr<ICellBehavior>()> behavior_factory;
};

const CellProperties CELL_PROPERTIES[] = {
    { CellType::None, 0.0f, BLACK },
    { CellType::Powder, 1.1f, YELLOW },
    { CellType::Liquid, 1.0f, BLUE },
    { CellType::Liquid, 0.7f, BROWN },
    { CellType::Plasma, 0.05f, RED, []() { return std::make_unique<FireBehavior>(); } },
    { CellType::Gas, 0.03f, GRAY },
};

class Cell {
public:
    bool moved = false;
    IVec2 velocity = IVec2(0, 0);
    int bias;
    CellDefinition definition;
    std::unique_ptr<ICellBehavior> behavior;

    Cell(CellDefinition definition);

    const CellProperties& get_properties() const;
};
