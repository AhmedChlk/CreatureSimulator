#pragma once
#include <SFML/System/Vector2.hpp>
#include <cmath>

namespace m2d {

inline sf::Vector2f operator+(const sf::Vector2f& a, const sf::Vector2f& b) { return {a.x+b.x, a.y+b.y}; }
inline sf::Vector2f operator-(const sf::Vector2f& a, const sf::Vector2f& b) { return {a.x-b.x, a.y-b.y}; }
inline sf::Vector2f operator*(const sf::Vector2f& a, float s) { return {a.x*s, a.y*s}; }
inline sf::Vector2f operator/(const sf::Vector2f& a, float s) { return {a.x/s, a.y/s}; }

inline sf::Vector2f& operator+=(sf::Vector2f& a, const sf::Vector2f& b) { a.x+=b.x; a.y+=b.y; return a; }
inline sf::Vector2f& operator-=(sf::Vector2f& a, const sf::Vector2f& b) { a.x-=b.x; a.y-=b.y; return a; }
inline sf::Vector2f& operator*=(sf::Vector2f& a, float s) { a.x*=s; a.y*=s; return a; }

inline float dot(const sf::Vector2f& a, const sf::Vector2f& b) { return a.x*b.x + a.y*b.y; }
inline float len2(const sf::Vector2f& v) { return dot(v,v); }
inline float len(const sf::Vector2f& v) { return std::sqrt(len2(v)); }

inline sf::Vector2f safeNorm(const sf::Vector2f& v) {
    float L = len(v);
    if (L < 1e-6f) return {0.f, 0.f};
    return v / L;
}

template<typename T>
inline T clamp(T v, T lo, T hi) {
    return (v < lo) ? lo : (v > hi ? hi : v);
}

} // namespace m2d
