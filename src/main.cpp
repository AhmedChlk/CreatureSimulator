#include <SFML/Graphics.hpp>
#include "Creature.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Creature Simulator");
    const sf::Color backgroundColor = sf::Color(139, 69, 19);

    Creature creature;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        window.clear(backgroundColor);
        creature.draw(window);
        window.display();
    }

    return 0;
}
