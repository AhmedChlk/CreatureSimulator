#pragma once
#include <SFML/System/Vector2.hpp>
#include <cstddef>
#include <memory>
#include <vector>

#include "PhysicalPoint.hpp"
#include "Constraint.hpp"

class PhysicsWorld {
public:
    PhysicsWorld();
    ~PhysicsWorld() = default;

    PhysicsWorld(const PhysicsWorld&) = delete;
    PhysicsWorld& operator=(const PhysicsWorld&) = delete;
    PhysicsWorld(PhysicsWorld&&) noexcept = default;
    PhysicsWorld& operator=(PhysicsWorld&&) noexcept = default;

    void setGravity(const sf::Vector2f& g);
    const sf::Vector2f& gravity() const;

    void setDamping(float d);
    float damping() const;

    void setGround(float y);
    float groundY() const;

    void setGroundFriction(float f);
    float groundFriction() const;

    std::size_t addPoint(const PhysicalPoint& p);
    std::size_t addPoint(const sf::Vector2f& pos, float mass);

    template <typename TConstraint, typename... Args>
    TConstraint& addConstraint(Args&&... args) {
        auto ptr = std::make_unique<TConstraint>(std::forward<Args>(args)...);
        TConstraint& ref = *ptr;
        m_constraints.emplace_back(std::move(ptr));
        return ref;
    }

    std::size_t pointCount() const;
    std::size_t constraintCount() const;

    PhysicalPoint& point(std::size_t i);
    const PhysicalPoint& point(std::size_t i) const;

    const std::vector<std::unique_ptr<Constraint>>& constraints() const;

    void step(float dt, int solverIterations = 10);
    
    // --- AJOUT ---
    void reset();
    // -------------

private:
    void integrate(float dt);
    void solveConstraints(float dt, int iterations);
    void updateVelocities(float dt);
    void solveGround(float dt);

private:
    std::vector<PhysicalPoint> m_points;
    std::vector<std::unique_ptr<Constraint>> m_constraints;

    sf::Vector2f m_gravity{0.f, 980.f};
    float m_damping{0.995f};

    float m_groundY{600.f};
    float m_groundFriction{0.85f};
};