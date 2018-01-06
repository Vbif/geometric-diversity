#pragma once

#include "Utils/FLine.h"

class FCircle {
public:
    FPoint center;
    float radius;

public:
    FCircle(const FPoint& c, float r)
        : center(c)
        , radius(r)
    {
    }

    bool Intersects(const FLine& line, FPoint* targetPoint) const;
    bool Intersects(const FCircle& that) const;
};
