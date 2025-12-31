#include "DistanceConstraint.hpp"
#include "PhysicsWorld.hpp"
#include <cmath>

// Constructeur utilisant les indices (size_t) comme déclaré dans le .hpp
DistanceConstraint::DistanceConstraint(std::size_t a, std::size_t b, float restLength, float stiffness)
    : m_a(a), m_b(b), m_rest(restLength), m_stiffness(stiffness)
{
}

void DistanceConstraint::solve(PhysicsWorld& world, float /*dt*/) {
    // 1. On récupère les vrais points grâce à l'objet world et nos indices
    PhysicalPoint& p1 = world.point(m_a);
    PhysicalPoint& p2 = world.point(m_b);

    // 2. On récupère les positions avec les getters
    sf::Vector2f p1Pos = p1.getPosition();
    sf::Vector2f p2Pos = p2.getPosition();

    sf::Vector2f delta = p2Pos - p1Pos;
    float currentDist = std::sqrt(delta.x * delta.x + delta.y * delta.y);

    if (currentDist < 0.0001f) return; // Évite la division par zéro

    // 3. Calcul de la correction (PBD)
    float difference = (currentDist - m_rest) / currentDist;
    sf::Vector2f correction = delta * difference * 0.5f * m_stiffness;

    // 4. Application des nouvelles positions via les setters (si pas fixés)
    if (!p1.isFixed())
        p1.setPosition(p1Pos + correction);
    
    if (!p2.isFixed())
        p2.setPosition(p2Pos - correction);
}

std::pair<std::size_t, std::size_t> DistanceConstraint::endpoints() const {
    return {m_a, m_b};
}

float DistanceConstraint::targetLength() const {
    return m_rest;
}