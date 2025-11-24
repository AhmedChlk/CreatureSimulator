#include "BodyPart.hpp"

BodyPart::BodyPart(BodyPartType type, const sf::Vector2f& position)
    : type(type), position(position) {}

BodyPartType BodyPart::getType() const { return type; }
sf::Vector2f BodyPart::getPosition() const { return position; }
