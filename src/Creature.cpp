#include "Creature.hpp"
#include <cstdlib> // rand
#include <ctime>

Creature::Creature() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    generateRandom();
}

void Creature::generateRandom() {
    int numParts = 3 + rand() % 5; // 3 à 7 parties au hasard

    // Génération aléatoire des BodyParts
    for (int i = 0; i < numParts; ++i) {
        BodyPartType type;
        if (i == 0) type = BodyPartType::HEAD;
        else if (i == 1) type = BodyPartType::BODY;
        else type = BodyPartType::LIMB;

        float x = 100 + rand() % 600;
        float y = 100 + rand() % 400;
        parts.emplace_back(type, sf::Vector2f(x, y));
    }

    // Lier tous les BodyParts pour que la créature soit attachée
    for (size_t i = 1; i < parts.size(); ++i) {
        links.emplace_back(&parts[i-1], &parts[i], 50.0f);
    }
}

void Creature::draw(sf::RenderWindow& window) {
    // Dessiner les liens
    for (auto& link : links) {
        sf::Vertex line[] = {
            sf::Vertex(link.getA()->getPosition(), sf::Color::White),
            sf::Vertex(link.getB()->getPosition(), sf::Color::White)
        };
        window.draw(line, 2, sf::Lines);
    }

    // Dessiner les BodyParts
    for (auto& part : parts) {
        sf::CircleShape circle(10);
        circle.setPosition(part.getPosition() - sf::Vector2f(10,10));
        switch(part.getType()) {
            case BodyPartType::HEAD: circle.setFillColor(sf::Color::Red); break;
            case BodyPartType::BODY: circle.setFillColor(sf::Color::Green); break;
            case BodyPartType::LIMB: circle.setFillColor(sf::Color::Blue); break;
        }
        window.draw(circle);
    }
}
