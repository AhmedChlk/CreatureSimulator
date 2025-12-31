#pragma once
#include "Constraint.hpp"
#include <cmath>

class JointConstraint : public Constraint {
public:
    // Constructeur complet avec force max et raideur
    JointConstraint(std::size_t a, std::size_t b, float length, float maxForce, float stiffness = 0.5f);

    void solve(PhysicsWorld& world, float dt) override;

    std::pair<std::size_t, std::size_t> endpoints() const override;
    float targetLength() const override;

    void setTargetLength(float len);
    float baseLength() const; // Pour le calcul du cycle de marche
    float maxForce() const;   // Pour le calcul de l'énergie

private:
    std::size_t m_a;
    std::size_t m_b;
    float m_length;      // Longueur actuelle cible
    float m_baseLength;  // Longueur initiale (repos)
    float m_maxForce;
    float m_stiffness;
};