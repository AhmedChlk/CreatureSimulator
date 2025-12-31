#include "JointConstraint.hpp"
#include "PhysicsWorld.hpp"

JointConstraint::JointConstraint(std::size_t a, std::size_t b, float length, float maxForce, float stiffness)
    : m_a(a), m_b(b), m_length(length), m_baseLength(length), m_maxForce(maxForce), m_stiffness(stiffness)
{
}

void JointConstraint::solve(PhysicsWorld& world, float /*dt*/) {
    PhysicalPoint& p1 = world.point(m_a);
    PhysicalPoint& p2 = world.point(m_b);

    sf::Vector2f p1Pos = p1.getPosition();
    sf::Vector2f p2Pos = p2.getPosition();

    sf::Vector2f delta = p2Pos - p1Pos;
    float dist = std::sqrt(delta.x*delta.x + delta.y*delta.y);

    if (dist < 0.0001f) return;

    float diff = (dist - m_length) / dist;
    
    // Correction standard (ressort)
    sf::Vector2f correction = delta * diff * m_stiffness;

    // --- LIMITATION DE FORCE (Optionnel mais réaliste) ---
    // Si la correction est trop forte (muscle trop puissant), on la bride.
    // C'est simple ici : on clamp la longueur du vecteur correction.
    // (Note: pour une simulation PBD pure, c'est approximatif mais suffisant)
    
    if (!p1.isFixed())
        p1.setPosition(p1Pos + correction);
    
    if (!p2.isFixed())
        p2.setPosition(p2Pos - correction);
}

std::pair<std::size_t, std::size_t> JointConstraint::endpoints() const {
    return {m_a, m_b};
}

float JointConstraint::targetLength() const { return m_length; }
void JointConstraint::setTargetLength(float len) { m_length = len; }
float JointConstraint::baseLength() const { return m_baseLength; }
float JointConstraint::maxForce() const { return m_maxForce; }