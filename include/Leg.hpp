#pragma once
#include <vector>
#include <cstddef>

class LimbSegment;

class Leg {
public:
    Leg(std::size_t hip,
        std::size_t knee,
        std::size_t foot);

    void addSegment(const LimbSegment& seg);

    std::size_t hip() const { return m_hip; }
    std::size_t knee() const { return m_knee; }
    std::size_t foot() const { return m_foot; }

private:
    std::size_t m_hip;
    std::size_t m_knee;
    std::size_t m_foot;
};
