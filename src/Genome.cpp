#include "Genome.hpp"
#include "Math2D.hpp"
#include <algorithm>

Genome Genome::random(std::mt19937& rng) {
    std::uniform_real_distribution<float> u01(0.f, 1.f);

    Genome g;
    g.bodyW = 90.f  + 120.f * u01(rng);
    g.bodyH = 40.f  +  70.f * u01(rng);
    g.legUpper = 45.f +  70.f * u01(rng);
    g.legLower = 55.f +  80.f * u01(rng);

    g.hipMaxForce  = 600.f + 1200.f * u01(rng);
    g.kneeMaxForce = 600.f + 1200.f * u01(rng);

    g.hipAmp  = 0.10f + 0.35f * u01(rng);
    g.kneeAmp = 0.10f + 0.40f * u01(rng);

    g.frequency = 0.8f + 2.2f * u01(rng);

    // phases de base (trot)
    g.phaseFL = 0.f;
    g.phaseBR = 0.f;
    g.phaseFR = 3.14159f;
    g.phaseBL = 3.14159f;

    // petite randomisation
    auto jitter = [&](float& ph){
        ph += (u01(rng)-0.5f) * 0.5f;
    };
    jitter(g.phaseFL); jitter(g.phaseFR); jitter(g.phaseBL); jitter(g.phaseBR);

    return g;
}

Genome Genome::mutated(std::mt19937& rng) const {
    std::normal_distribution<float> n01(0.f, 1.f);

    Genome c = *this;

    auto mut = [&](float& v, float sigma, float lo, float hi){
        v += sigma * n01(rng);
        v = m2d::clamp(v, lo, hi);
    };

    mut(c.bodyW, 10.f, 70.f, 220.f);
    mut(c.bodyH,  8.f, 30.f, 120.f);

    mut(c.legUpper, 8.f, 30.f, 130.f);
    mut(c.legLower, 8.f, 30.f, 150.f);

    mut(c.hipMaxForce, 120.f, 200.f, 2500.f);
    mut(c.kneeMaxForce,120.f, 200.f, 2500.f);

    mut(c.hipAmp,  0.03f, 0.02f, 0.55f);
    mut(c.kneeAmp, 0.03f, 0.02f, 0.60f);

    mut(c.frequency, 0.15f, 0.4f, 3.5f);

    // phases
    mut(c.phaseFL, 0.10f, -6.28f, 6.28f);
    mut(c.phaseFR, 0.10f, -6.28f, 6.28f);
    mut(c.phaseBL, 0.10f, -6.28f, 6.28f);
    mut(c.phaseBR, 0.10f, -6.28f, 6.28f);

    return c;
}
