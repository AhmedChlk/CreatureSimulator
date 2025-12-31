#include "PhysicalPoint.hpp"

PhysicalPoint::PhysicalPoint(const sf::Vector2f& pos, float mass)
: m_pos(pos), m_prevPos(pos), m_mass(mass) {}

void PhysicalPoint::setFixed(bool fixed) { m_fixed = fixed; }
bool PhysicalPoint::isFixed() const { return m_fixed; }

void PhysicalPoint::setMass(float m) { m_mass = m; }
float PhysicalPoint::mass() const { return m_mass; }

void PhysicalPoint::setPosition(const sf::Vector2f& p) { m_pos = p; }
const sf::Vector2f& PhysicalPoint::getPosition() const { return m_pos; }

void PhysicalPoint::setVelocity(const sf::Vector2f& v) { m_vel = v; }
const sf::Vector2f& PhysicalPoint::getVelocity() const { return m_vel; }

void PhysicalPoint::clearForces() { m_force = {0.f, 0.f}; }
void PhysicalPoint::addForce(const sf::Vector2f& f) { m_force.x += f.x; m_force.y += f.y; }
const sf::Vector2f& PhysicalPoint::getAccumulatedForce() const { return m_force; }

void PhysicalPoint::storePrevPosition() { m_prevPos = m_pos; }
const sf::Vector2f& PhysicalPoint::prevPosition() const { return m_prevPos; }
