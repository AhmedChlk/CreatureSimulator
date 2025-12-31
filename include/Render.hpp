#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "PhysicsWorld.hpp"

namespace Render {
    void drawWorld(sf::RenderTarget& target, const PhysicsWorld& world, bool drawPoints = true, bool drawConstraints = true);
    void drawGround(sf::RenderTarget& target, float y, float w);
    void drawGraph(sf::RenderTarget& target, const std::vector<float>& values, sf::FloatRect area);
}
