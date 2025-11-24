#pragma once
#include <vector>
#include "BodyPart.hpp"
#include "Link.hpp"
#include <SFML/Graphics.hpp>

class Creature {
public:
    Creature(); // Génère la créature aléatoire
    void draw(sf::RenderWindow& window);

private:
    std::vector<BodyPart> parts;
    std::vector<Link> links;

    void generateRandom();
};
