#pragma once
#include <SFML/Graphics.hpp>

enum class BodyPartType { HEAD, BODY, LIMB };

class BodyPart {
public:
    BodyPart(BodyPartType type, const sf::Vector2f& position={0,0});

    BodyPartType getType() const;
    sf::Vector2f getPosition() const;

private:
    sf::Vector2f position;
    BodyPartType type;
};
