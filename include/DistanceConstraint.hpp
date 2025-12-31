#pragma once
#include "Constraint.hpp"

class DistanceConstraint : public Constraint {
public:
    DistanceConstraint(std::size_t a, std::size_t b, float restLength, float stiffness = 1.f);

    void solve(PhysicsWorld& world, float dt) override;

    std::pair<std::size_t, std::size_t> endpoints() const override;
    float targetLength() const override;

    float restLength() const { return m_rest; }
    void setStiffness(float s) { m_stiffness = s; }

private:
    std::size_t m_a{}, m_b{};
    float m_rest{10.f};
    float m_stiffness{1.f};
};
