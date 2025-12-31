#include "Population.hpp"
#include <algorithm>

Population::Population(std::size_t size, unsigned seed)
    : m_rng(seed)
{
    m_genomes.resize(size);
    m_fit.resize(size);

    // Génomes init aléatoires
    for (auto& g : m_genomes) {
        // CORRECTION 1 : random est statique et renvoie un objet, ce n'est pas une modif sur place
        g = Genome::random(m_rng); 
    }
}

// Implémentation des accesseurs manquants (nécessaire pour éviter des erreurs de lien)
std::size_t Population::size() const { return m_genomes.size(); }
const std::vector<Genome>& Population::genomes() const { return m_genomes; }
const std::vector<Fitness>& Population::fitnesses() const { return m_fit; }
std::size_t Population::generation() const { return m_generation; }

// CORRECTION : Implémentation de bestIndex
std::size_t Population::bestIndex() const { 
    return m_bestIndex; 
}

void Population::setFitness(std::size_t i, const Fitness& f) {
    if (i < m_fit.size()) {
        m_fit[i] = f;
    }
}

void Population::evaluateGeneration(float /*simSeconds*/) {
    // Sera rempli plus tard avec la simulation physique
}

void Population::computeScores() {
    if (m_fit.empty()) {
        m_bestIndex = 0;
        return;
    }

    m_bestIndex = 0;
    for (std::size_t i = 1; i < m_fit.size(); ++i) {
        // On suppose que Fitness a un membre 'score' (float ou double)
        if (m_fit[i].score > m_fit[m_bestIndex].score) {
            m_bestIndex = i;
        }
    }
}

void Population::nextGeneration() {
    computeScores();

    // Tri des indices par score décroissant
    std::vector<std::size_t> order(m_genomes.size());
    for (std::size_t i = 0; i < order.size(); ++i) order[i] = i;

    std::sort(order.begin(), order.end(), [&](std::size_t a, std::size_t b) {
        return m_fit[a].score > m_fit[b].score;
    });

    // On garde le top 25% comme parents
    std::size_t eliteCount = std::max<std::size_t>(1, m_genomes.size() / 4);

    std::vector<Genome> newGen;
    newGen.reserve(m_genomes.size());

    // Elites copiés
    for (std::size_t i = 0; i < eliteCount; ++i) {
        newGen.push_back(m_genomes[order[i]]);
    }

    // Reproduction + mutation
    std::uniform_int_distribution<std::size_t> parentDist(0, eliteCount - 1);

    while (newGen.size() < m_genomes.size()) {
        Genome child = newGen[parentDist(m_rng)];  // clone d’un parent
        
        // CORRECTION 2 : mutated renvoie une copie modifiée, elle ne modifie pas 'child' directement
        child = child.mutated(m_rng);                       
        
        newGen.push_back(child);
    }

    m_genomes = std::move(newGen);
    m_generation++;
}