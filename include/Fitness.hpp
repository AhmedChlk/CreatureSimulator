#pragma once

struct Fitness {
    float distance = 0.f;
    float energy   = 0.f;
    float mass     = 0.f;
    float score    = 0.f;

    static Fitness make(float dist, float energy, float mass);
};
