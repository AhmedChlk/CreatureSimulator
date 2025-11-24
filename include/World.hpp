#pragma once
#include <vector>
#include "Creature.hpp"
#include <SFML/Graphics.hpp>

class World {
public:
    std::vector<Creature> creatures;

    World();

    void spawnRandomCreatures(int n);
    void update(float dt);
    void draw(sf::RenderWindow& window);
};
