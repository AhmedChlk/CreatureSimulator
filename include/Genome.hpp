#pragma once
#include <random>

struct Genome {
    // Morphologie
    float bodyW = 120.f;
    float bodyH = 60.f;

    float legUpper = 65.f;
    float legLower = 75.f;

    // Muscles
    float hipMaxForce  = 900.f;
    float kneeMaxForce = 900.f;

    float hipAmp  = 0.25f; // contraction %
    float kneeAmp = 0.30f;

    // Gait
    float frequency = 1.6f;  // Hz
    float phaseFL = 0.0f;
    float phaseFR = 3.14159f;
    float phaseBL = 3.14159f;
    float phaseBR = 0.0f;

    static Genome random(std::mt19937& rng);
    Genome mutated(std::mt19937& rng) const;
};
