#pragma once
#include "BodyPart.hpp"

class Link {
public:
    Link(BodyPart* p1, BodyPart* p2, float length);

    BodyPart* getA() const { return a; }
    BodyPart* getB() const { return b; }
    float getRestLength() const { return restLength; }

private:
    BodyPart* a;
    BodyPart* b;
    float restLength;
};
