#include "LimbSegment.hpp"
#include "PhysicsWorld.hpp"
#include "DistanceConstraint.hpp"
#include <memory>

LimbSegment::LimbSegment(PhysicsWorld& world,
                         std::size_t a,
                         std::size_t b,
                         float restLength,
                         float stiffness)
    : m_a(a), m_b(b)
{
    world.addConstraint(
        std::make_unique<DistanceConstraint>(a, b, restLength, stiffness)
    );
}
