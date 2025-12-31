#include "LimbSegment.hpp"
#include "PhysicsWorld.hpp"
#include "DistanceConstraint.hpp"

LimbSegment::LimbSegment(PhysicsWorld& world,
                         std::size_t a,
                         std::size_t b,
                         float restLength,
                         float stiffness)
    : m_a(a), m_b(b)
{
    // IMPORTANT: PhysicsWorld::addConstraint est une template
    // => on appelle addConstraint<DistanceConstraint>(...)
    world.addConstraint<DistanceConstraint>(a, b, restLength, stiffness);
}
