#include "cell.hpp"
#include "sandbox.hpp"

#include <random>

extern std::default_random_engine rng;

void FireBehavior::update(Sandbox& sandbox, IVec2 position) {
}

const CellProperties& Cell::get_properties() const {
    return CELL_PROPERTIES[(size_t) definition];
}

Cell::Cell(CellDefinition definition)
    : definition(definition),
    behavior((get_properties().behavior_factory) ? get_properties().behavior_factory() : nullptr)
{
    static std::bernoulli_distribution distribution(0.5);

    bias = distribution(rng) ? -1 : 1;
}
