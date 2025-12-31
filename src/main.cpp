#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "PhysicsWorld.hpp"
#include "Creature.hpp"
#include "Population.hpp"
#include "Fitness.hpp"
#include "Render.hpp"

static Fitness evaluateOne(const Genome& g, float simSeconds) {
    PhysicsWorld world;
    world.setGravity({0.f, 980.f});
    world.setGround(600.f);
    world.setDamping(0.995f);
    world.setGroundFriction(0.85f);

    Creature c(world, g, {200.f, 520.f});
    const sf::Vector2f start = c.centerOfMass();

    const float dt = 1.f / 120.f;
    float t = 0.f;

    while (t < simSeconds) {
        c.updateControllers(t, dt);
        world.step(dt, 12);
        t += dt;
    }

    const sf::Vector2f end = c.centerOfMass();
    float dist = end.x - start.x;
    return Fitness::make(dist, c.energySpent(), c.approximateMass());
}

int main() {
    const unsigned W = 1000, H = 700;
    sf::RenderWindow window(sf::VideoMode(W, H), "Quad Physics - Phase 3 (Evolution)");
    window.setFramerateLimit(60);

    // UI
    sf::Font font;
    bool fontOk = font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");

    const std::size_t POP = 60;
    const float SIM_SECONDS = 4.0f;

    Population pop(POP, 1337);
    std::vector<float> historyBestScore;

    // Eval gen 0
    for (std::size_t i = 0; i < pop.size(); ++i) {
        pop.setFitness(i, evaluateOne(pop.genomes()[i], SIM_SECONDS));
    }
    std::size_t bestIdx = pop.bestIndex();
    historyBestScore.push_back(pop.fitnesses()[bestIdx].score);

    // Affichage du best
    PhysicsWorld displayWorld;
    displayWorld.setGravity({0.f, 980.f});
    displayWorld.setGround(600.f);
    displayWorld.setDamping(0.995f);
    displayWorld.setGroundFriction(0.85f);

    // IMPORTANT: Creature non-assignable => on passe par unique_ptr
    std::unique_ptr<Creature> best = std::make_unique<Creature>(displayWorld, pop.genomes()[bestIdx], sf::Vector2f{200.f, 520.f});

    float simT = 0.f;
    float genTimer = 0.f;

    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) window.close();
        }

        const float dt = 1.f / 60.f;
        genTimer += dt;

        // toutes les ~2.5 sec => nouvelle génération
        if (genTimer > 2.5f) {
            genTimer = 0.f;

            // next gen
            pop.nextGeneration();

            // évaluer
            for (std::size_t i = 0; i < pop.size(); ++i) {
                pop.setFitness(i, evaluateOne(pop.genomes()[i], SIM_SECONDS));
            }
            bestIdx = pop.bestIndex();
            historyBestScore.push_back(pop.fitnesses()[bestIdx].score);

            // reset affichage best
            displayWorld = PhysicsWorld(); // move OK (move explicit)
            displayWorld.setGravity({0.f, 980.f});
            displayWorld.setGround(600.f);
            displayWorld.setDamping(0.995f);
            displayWorld.setGroundFriction(0.85f);

            best = std::make_unique<Creature>(displayWorld, pop.genomes()[bestIdx], sf::Vector2f{200.f, 520.f});
            simT = 0.f;
        }

        // sim visuelle du best
        for (int k = 0; k < 2; ++k) { // 2 sous-steps pour stabilité
            best->updateControllers(simT, dt/2.f);
            displayWorld.step(dt/2.f, 12);
            simT += dt/2.f;
        }

        window.clear(sf::Color(15, 15, 18));
        Render::drawGround(window, displayWorld.groundY(), (float)W);
        Render::drawWorld(window, displayWorld, true, true);

        // HUD
        if (fontOk) {
            sf::Text t;
            t.setFont(font);
            t.setCharacterSize(16);
            t.setFillColor(sf::Color(240,240,240));

            const Fitness& f = pop.fitnesses()[bestIdx];
            t.setString(
                "Gen: " + std::to_string(pop.generation()) +
                " | Best score: " + std::to_string((int)f.score) +
                " | dist: " + std::to_string((int)f.distance) +
                " | mass: " + std::to_string((int)f.mass) +
                " | energy: " + std::to_string((int)f.energy)
            );
            t.setPosition(12.f, 10.f);
            window.draw(t);
        }

        // graphe
        Render::drawGraph(window, historyBestScore, sf::FloatRect{650.f, 40.f, 330.f, 140.f});

        window.display();
    }

    return 0;
}
