#include "Render.hpp"
#include "Math2D.hpp"

namespace Render {

void drawGround(sf::RenderTarget& target, float y, float w) {
    sf::RectangleShape r;
    r.setSize({w, 4.f});
    r.setPosition({0.f, y});
    r.setFillColor(sf::Color(120, 120, 120));
    target.draw(r);
}

void drawWorld(sf::RenderTarget& target, const PhysicsWorld& world, bool drawPoints, bool drawConstraints) {
    if (drawConstraints) {
        for (const auto& c : world.constraints()) {
            auto [a,b] = c->endpoints();
            auto pa = world.point(a).getPosition();
            auto pb = world.point(b).getPosition();

            sf::Vertex line[2] = {
                sf::Vertex(pa, sf::Color(230, 230, 230)),
                sf::Vertex(pb, sf::Color(230, 230, 230))
            };
            target.draw(line, 2, sf::Lines);
        }
    }

    if (drawPoints) {
        sf::CircleShape dot;
        dot.setRadius(3.f);
        dot.setOrigin({3.f,3.f});

        for (std::size_t i = 0; i < world.pointCount(); ++i) {
            const auto& p = world.point(i);
            dot.setPosition(p.getPosition());
            dot.setFillColor(p.isFixed() ? sf::Color(255,140,90) : sf::Color(90,200,255));
            target.draw(dot);
        }
    }
}

void drawGraph(sf::RenderTarget& target, const std::vector<float>& values, sf::FloatRect area) {
    if (values.size() < 2) return;

    float minV = values[0], maxV = values[0];
    for (float v : values) { if (v < minV) minV = v; if (v > maxV) maxV = v; }
    if (std::abs(maxV - minV) < 1e-6f) { maxV = minV + 1.f; }

    sf::RectangleShape bg;
    bg.setPosition({area.left, area.top});
    bg.setSize({area.width, area.height});
    bg.setFillColor(sf::Color(20,20,20,160));
    target.draw(bg);

    std::vector<sf::Vertex> line(values.size());
    for (std::size_t i = 0; i < values.size(); ++i) {
        float u = (float)i / (float)(values.size()-1);
        float v = (values[i] - minV) / (maxV - minV);
        float x = area.left + u * area.width;
        float y = area.top + (1.f - v) * area.height;
        line[i] = sf::Vertex({x,y}, sf::Color(120,255,120));
    }
    target.draw(line.data(), line.size(), sf::LineStrip);
}

} // namespace Render
