#pragma once
#include "Fitness.hpp"
#include "Genome.hpp"
#include <random>

class Evaluator {
public:
    explicit Evaluator(FitnessConfig cfg);

    FitnessResult evaluate(const Genome& g) const;

private:
    FitnessConfig m_cfg;
};
