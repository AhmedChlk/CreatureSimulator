#pragma once
#include <SFML/Graphics.hpp>
#include <cstddef>
#include <vector>

#include "PhysicsWorld.hpp"
#include "Genome.hpp"
#include "JointConstraint.hpp"

class Creature {
public:
    Creature(PhysicsWorld& world, const Genome& g, const sf::Vector2f& spawn);

    void updateControllers(float timeSeconds, float dt);
    void draw(sf::RenderTarget& target) const;

    sf::Vector2f centerOfMass() const;
    float approximateMass() const;
    float energySpent() const;

private:
    struct LegRefs {
        std::size_t hip{};
        std::size_t knee{};
        std::size_t foot{};
        JointConstraint* hipMuscle{nullptr};
        JointConstraint* kneeMuscle{nullptr};
        float phase{0.f};
    };

    LegRefs makeLeg(const sf::Vector2f& hipPos, float phase, bool isFront);

private:
    PhysicsWorld& m_world;
    Genome m_g;

    // body points
    std::size_t m_a{}, m_b{}, m_c{}, m_d{};

    // legs (FL, FR, BL, BR)
    LegRefs m_fl, m_fr, m_bl, m_br;

    float m_energy{0.f};
};
