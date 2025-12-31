#pragma once
#include <cstddef>
#include <utility>

class PhysicsWorld;

class Constraint {
public:
    virtual ~Constraint() = default;

    // PBD solve: ajuste les positions
    virtual void solve(PhysicsWorld& world, float dt) = 0;

    // debug: pour Render
    virtual std::pair<std::size_t, std::size_t> endpoints() const = 0;
    virtual float targetLength() const = 0;
};
