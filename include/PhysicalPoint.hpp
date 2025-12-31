#pragma once
#include <SFML/System/Vector2.hpp>

class PhysicalPoint {
public:
    PhysicalPoint() = default;
    PhysicalPoint(const sf::Vector2f& pos, float mass);

    void setFixed(bool fixed);
    bool isFixed() const;

    void setMass(float m);
    float mass() const;

    void setPosition(const sf::Vector2f& p);
    const sf::Vector2f& getPosition() const;

    void setVelocity(const sf::Vector2f& v);
    const sf::Vector2f& getVelocity() const;

    // Aliases (pour éviter les bugs "position()/velocity()" dans ton main)
    const sf::Vector2f& position() const { return m_pos; }
    const sf::Vector2f& velocity() const { return m_vel; }

    void clearForces();
    void addForce(const sf::Vector2f& f);
    const sf::Vector2f& getAccumulatedForce() const;

    // PBD support
    void storePrevPosition();
    const sf::Vector2f& prevPosition() const;

private:
    sf::Vector2f m_pos{0.f, 0.f};
    sf::Vector2f m_prevPos{0.f, 0.f};
    sf::Vector2f m_vel{0.f, 0.f};
    sf::Vector2f m_force{0.f, 0.f};
    float m_mass{1.f};
    bool m_fixed{false};
};
