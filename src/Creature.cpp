#include "Creature.hpp"
#include "DistanceConstraint.hpp"
#include "Math2D.hpp" // Assure-toi d'avoir m2d::dist ou std::hypot
#include <cmath>

static float s01(float x) {
    return 0.5f * (std::sin(x) + 1.f);
}

// Petite fonction utilitaire locale pour calculer la distance
static float distPoints(const PhysicsWorld& world, std::size_t ia, std::size_t ib) {
    sf::Vector2f pa = world.point(ia).getPosition();
    sf::Vector2f pb = world.point(ib).getPosition();
    sf::Vector2f d = pb - pa;
    return std::sqrt(d.x*d.x + d.y*d.y);
}

Creature::Creature(PhysicsWorld& world, const Genome& g, const sf::Vector2f& spawn)
: m_world(world), m_g(g) {
    m_world.setGround(600.f);
    m_world.setDamping(0.995f);
    m_world.setGroundFriction(0.85f);

    const float w = m_g.bodyW;
    const float h = m_g.bodyH;

    // body rectangle: A(TL) B(TR) C(BL) D(BR)
    // Attention : l'ordre Y dépend de ton repère (Y vers le bas en SFML)
    m_a = m_world.addPoint({spawn.x,     spawn.y - h}, 1.2f);
    m_b = m_world.addPoint({spawn.x + w, spawn.y - h}, 1.2f);
    m_c = m_world.addPoint({spawn.x,     spawn.y     }, 1.2f); // Bas Gauche
    m_d = m_world.addPoint({spawn.x + w, spawn.y     }, 1.2f); // Bas Droite

    // Torso constraints (rigide)
    m_world.addConstraint<DistanceConstraint>(m_a, m_b, w, 1.f);
    m_world.addConstraint<DistanceConstraint>(m_c, m_d, w, 1.f);
    m_world.addConstraint<DistanceConstraint>(m_a, m_c, h, 1.f);
    m_world.addConstraint<DistanceConstraint>(m_b, m_d, h, 1.f);

    // Diagonales (croix)
    float diag = std::sqrt(w*w + h*h);
    m_world.addConstraint<DistanceConstraint>(m_a, m_d, diag, 1.f);
    m_world.addConstraint<DistanceConstraint>(m_b, m_c, diag, 1.f);

    // --- CRÉATION DES JAMBES ---
    
    // Positions cibles pour les hanches
    sf::Vector2f posC = m_world.point(m_c).getPosition();
    sf::Vector2f posD = m_world.point(m_d).getPosition();
    sf::Vector2f posA = m_world.point(m_a).getPosition();
    sf::Vector2f posB = m_world.point(m_b).getPosition();

    sf::Vector2f hipFL = posC + sf::Vector2f{ 10.f,  0.f};
    sf::Vector2f hipFR = posD + sf::Vector2f{-10.f,  0.f};
    sf::Vector2f hipBL = posA + sf::Vector2f{ 10.f,  0.f};
    sf::Vector2f hipBR = posB + sf::Vector2f{-10.f,  0.f};

    m_fl = makeLeg(hipFL, m_g.phaseFL, true);
    m_fr = makeLeg(hipFR, m_g.phaseFR, true);
    m_bl = makeLeg(hipBL, m_g.phaseBL, false);
    m_br = makeLeg(hipBR, m_g.phaseBR, false);

    // --- FIX CRUCIAL : ATTACHER LES JAMBES AU CORPS ---
    // Pour que la hanche tienne solide au corps, on l'attache à 2 points du corps (triangulation).
    
    // Front Left Leg (attachée à C et D pour rigidité latérale, ou C et A pour verticale)
    // Ici on attache au coin le plus proche (C) + un autre (D) pour verrouiller la rotation
    m_world.addConstraint<DistanceConstraint>(m_c, m_fl.hip, distPoints(m_world, m_c, m_fl.hip), 1.0f);
    m_world.addConstraint<DistanceConstraint>(m_d, m_fl.hip, distPoints(m_world, m_d, m_fl.hip), 1.0f);

    // Front Right Leg (attachée à D et C)
    m_world.addConstraint<DistanceConstraint>(m_d, m_fr.hip, distPoints(m_world, m_d, m_fr.hip), 1.0f);
    m_world.addConstraint<DistanceConstraint>(m_c, m_fr.hip, distPoints(m_world, m_c, m_fr.hip), 1.0f);

    // Back Left Leg (attachée à A et B)
    m_world.addConstraint<DistanceConstraint>(m_a, m_bl.hip, distPoints(m_world, m_a, m_bl.hip), 1.0f);
    m_world.addConstraint<DistanceConstraint>(m_b, m_bl.hip, distPoints(m_world, m_b, m_bl.hip), 1.0f);

    // Back Right Leg (attachée à B et A)
    m_world.addConstraint<DistanceConstraint>(m_b, m_br.hip, distPoints(m_world, m_b, m_br.hip), 1.0f);
    m_world.addConstraint<DistanceConstraint>(m_a, m_br.hip, distPoints(m_world, m_a, m_br.hip), 1.0f);
}

Creature::LegRefs Creature::makeLeg(const sf::Vector2f& hipPos, float phase, bool isFront) {
    LegRefs L;
    L.phase = phase;

    // 1. Création du point de hanche (indépendant au début)
    L.hip  = m_world.addPoint(hipPos, 1.0f);

    // 2. Positions initiales genou et pied
    float kx = hipPos.x + (isFront ? 10.f : -10.f);
    float ky = hipPos.y + m_g.legUpper;

    float fx = kx + (isFront ? 15.f : -15.f);
    float fy = ky + m_g.legLower;

    L.knee = m_world.addPoint({kx, ky}, 0.9f);
    L.foot = m_world.addPoint({fx, fy}, 0.8f);

    // 3. Os (DistanceConstraint)
    m_world.addConstraint<DistanceConstraint>(L.hip, L.knee, m_g.legUpper, 1.f);
    m_world.addConstraint<DistanceConstraint>(L.knee, L.foot, m_g.legLower, 1.f);

    // 4. Muscles (JointConstraint)
    // On passe maintenant 5 arguments comme attendu par le nouveau constructeur
    L.hipMuscle  = &m_world.addConstraint<JointConstraint>(L.hip,  L.knee, m_g.legUpper, m_g.hipMaxForce, 1.f);
    L.kneeMuscle = &m_world.addConstraint<JointConstraint>(L.knee, L.foot, m_g.legLower, m_g.kneeMaxForce, 1.f);

    return L;
}

void Creature::updateControllers(float timeSeconds, float dt) {
    const float w = 2.f * 3.14159f * m_g.frequency;

    auto driveLeg = [&](LegRefs& L) {
        float x = w * timeSeconds + L.phase;
        float cyc = std::sin(x);

        // Contact au sol simple (si sin > 0, on considère qu'on veut pousser)
        // Dans une simu avancée, on détecterait la collision réelle.
        // Ici on triche un peu pour stabiliser : on fixe le pied s'il est bas.
        // Mais attention, fixer brutalement peut être bizarre.
        // Si tu veux laisser la physique faire : commente la ligne setFixed.
        // m_world.point(L.foot).setFixed(cyc > 0.f); 

        float a = s01(x); // 0..1
        float hipTarget  = L.hipMuscle->baseLength()  * (1.f - m_g.hipAmp  * a);
        float kneeTarget = L.kneeMuscle->baseLength() * (1.f - m_g.kneeAmp * (1.f - a));

        L.hipMuscle->setTargetLength(hipTarget);
        L.kneeMuscle->setTargetLength(kneeTarget);

        m_energy += (a * L.hipMuscle->maxForce() + a * L.kneeMuscle->maxForce()) * dt;
    };

    driveLeg(m_fl);
    driveLeg(m_fr);
    driveLeg(m_bl);
    driveLeg(m_br);
}

sf::Vector2f Creature::centerOfMass() const {
    auto pa = m_world.point(m_a).getPosition();
    auto pb = m_world.point(m_b).getPosition();
    auto pc = m_world.point(m_c).getPosition();
    auto pd = m_world.point(m_d).getPosition();
    return (pa + pb + pc + pd) / 4.f;
}

float Creature::approximateMass() const {
    // Somme très approximative (juste pour la fitness)
    return 10.f * 4.f; 
}

float Creature::energySpent() const { return m_energy; }

void Creature::draw(sf::RenderTarget& /*target*/) const {
    // Le dessin est géré par Render.cpp
}