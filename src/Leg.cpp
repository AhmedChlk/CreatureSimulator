#include "Leg.hpp"
#include "LimbSegment.hpp"

Leg::Leg(std::size_t hip,
         std::size_t knee,
         std::size_t foot)
    : m_hip(hip), m_knee(knee), m_foot(foot) {}

void Leg::addSegment(const LimbSegment&) {
    // Rien à stocker pour l’instant :
    // le segment existe physiquement dans le PhysicsWorld
}
