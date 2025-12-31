#pragma once
#include <random>
#include <vector>
#include "Genome.hpp"
#include "Fitness.hpp"

class Population {
public:
    Population(std::size_t size, unsigned seed = 42);

    std::size_t size() const;

    const std::vector<Genome>& genomes() const;
    const std::vector<Fitness>& fitnesses() const;

    void setFitness(std::size_t i, const Fitness& f);
    std::size_t bestIndex() const;

    void evaluateGeneration(float simSeconds); 
    void nextGeneration();
    std::size_t generation() const;

private:
    void computeScores();

    std::mt19937 m_rng;
    std::vector<Genome> m_genomes;
    std::vector<Fitness> m_fit;
    std::size_t m_generation{0};
    
    // --- CORRECTION ---
    // Ajout de la variable manquante
    std::size_t m_bestIndex{0}; 
};