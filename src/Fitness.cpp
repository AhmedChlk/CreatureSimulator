#include "Fitness.hpp"

Fitness Fitness::make(float dist, float energy, float mass) {
    Fitness f;
    f.distance = dist;
    f.energy = energy;
    f.mass = mass;

    // Phase 3: marcher vers +X efficacement
    // Tu peux ajuster les coefficients plus tard
    f.score = dist - 0.0025f * energy - 0.02f * mass;
    return f;
}
