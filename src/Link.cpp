#include "Link.hpp"

Link::Link(BodyPart* p1, BodyPart* p2, float length)
    : a(p1), b(p2), restLength(length) {}
