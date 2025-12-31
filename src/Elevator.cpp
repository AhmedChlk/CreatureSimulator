#include "Evaluator.hpp"
#include "PhysicsWorld.hpp"
#include "Creature.hpp"

Evaluator::Evaluator(FitnessConfig cfg) : m_cfg(cfg) {}

FitnessResult Evaluator::evaluate(const Genome& g) const {
    PhysicsWorld world;
    world.setGravity({0.f, 600.f}); // pixels/s² (ajuste)
    world.setDamping(0.995f);       // si tu l’as, sinon ignore

    // Sol
    world.setGroundY(520.f);        // ajoute cette variable si pas encore

    Creature c(world, g);

    const float startX = c.centerOfMass().x;

    for (int i = 0; i < (int)(m_cfg.simSeconds / m_cfg.dt); ++i) {
        c.update(m_cfg.dt);   // pilotage (horloge -> muscles)
        world.step(m_cfg.dt); // intégration + contraintes + collisions
    }

    FitnessResult r;
    const float endX = c.centerOfMass().x;
    r.distance = (endX - startX);
    r.energy = c.energySpent();
    r.mass = c.totalMass();

    r.score = r.distance
        - m_cfg.energyPenalty * r.energy
        - m_cfg.massPenalty * r.mass;

    return r;
}
