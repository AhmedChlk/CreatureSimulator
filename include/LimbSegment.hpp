#pragma once
#include <cstddef>

class PhysicsWorld;

class LimbSegment {
public:
    LimbSegment(PhysicsWorld& world,
                std::size_t a,
                std::size_t b,
                float restLength,
                float stiffness = 1.f);

    std::size_t a() const { return m_a; }
    std::size_t b() const { return m_b; }

private:
    std::size_t m_a;
    std::size_t m_b;
};
