#include "PhysicsWorld.hpp"
#include <algorithm>

PhysicsWorld::PhysicsWorld() = default;

void PhysicsWorld::setGravity(const sf::Vector2f& g) { m_gravity = g; }
const sf::Vector2f& PhysicsWorld::gravity() const { return m_gravity; }

void PhysicsWorld::setDamping(float d) { m_damping = d; }
float PhysicsWorld::damping() const { return m_damping; }

void PhysicsWorld::setGround(float y) { m_groundY = y; }
float PhysicsWorld::groundY() const { return m_groundY; }

void PhysicsWorld::setGroundFriction(float f) { m_groundFriction = f; }
float PhysicsWorld::groundFriction() const { return m_groundFriction; }

std::size_t PhysicsWorld::addPoint(const PhysicalPoint& p) {
    m_points.push_back(p);
    return m_points.size() - 1;
}

std::size_t PhysicsWorld::addPoint(const sf::Vector2f& pos, float mass) {
    PhysicalPoint p(pos, mass);
    m_points.push_back(p);
    return m_points.size() - 1;
}

std::size_t PhysicsWorld::pointCount() const { return m_points.size(); }
std::size_t PhysicsWorld::constraintCount() const { return m_constraints.size(); }

PhysicalPoint& PhysicsWorld::point(std::size_t i) { return m_points[i]; }
const PhysicalPoint& PhysicsWorld::point(std::size_t i) const { return m_points[i]; }

const std::vector<std::unique_ptr<Constraint>>& PhysicsWorld::constraints() const {
    return m_constraints;
}

// --- MOTEUR PHYSIQUE ROBUSTE (SUB-STEPPING) ---
void PhysicsWorld::step(float dt, int /*solverIterations*/) {
    // On divise le temps en 8 petites étapes pour éviter les explosions
    const int subSteps = 8;
    float subDt = dt / static_cast<float>(subSteps);

    for (int s = 0; s < subSteps; ++s) {
        integrate(subDt);
        solveGround(subDt);
        solveConstraints(subDt, 1); // 1 itération par sub-step suffit souvent
        updateVelocities(subDt);
    }
}

void PhysicsWorld::integrate(float dt) {
    for (auto& p : m_points) {
        if (p.isFixed()) continue;

        // Récupération des valeurs via les accesseurs
        sf::Vector2f pos = p.getPosition();
        sf::Vector2f vel = p.velocity(); // ou getVelocity()
        float mass = p.mass();
        sf::Vector2f forces = p.getAccumulatedForce();

        // F = ma => a = F/m
        sf::Vector2f accel = forces / mass;
        
        // v = v + a*dt
        vel += accel * dt;
        
        // p = p + v*dt
        pos += vel * dt;

        // Mise à jour de l'objet via les setters
        p.setVelocity(vel);
        p.setPosition(pos);

        // Reset des forces et réapplication de la gravité
        p.clearForces();
        p.addForce(m_gravity * mass);
    }
}

void PhysicsWorld::solveConstraints(float dt, int /*iterations*/) {
    // Note: On suppose que tes contraintes ont une méthode relax() ou solve()
    // Si tes contraintes héritent de 'Constraint', vérifie si la méthode s'appelle 'solve' ou 'relax'.
    // Ici j'utilise solve(*this, dt) comme défini dans ton Constraint.hpp probable.
    for (auto& c : m_constraints) {
        c->solve(*this, dt); 
    }
}

void PhysicsWorld::solveGround(float dt) {
    for (auto& p : m_points) {
        if (p.isFixed()) continue;

        sf::Vector2f pos = p.getPosition();
        sf::Vector2f vel = p.velocity();

        if (pos.y > m_groundY) {
            pos.y = m_groundY;
            vel.y = 0.f; // Stop vertical
            vel.x *= m_groundFriction; // Friction
            
            p.setPosition(pos);
            p.setVelocity(vel);
        }
    }
}

void PhysicsWorld::updateVelocities(float dt) {
    for (auto& p : m_points) {
        sf::Vector2f vel = p.velocity();
        vel *= m_damping;
        p.setVelocity(vel);
    }
}

void PhysicsWorld::reset() {
    m_points.clear();
    m_constraints.clear();
}