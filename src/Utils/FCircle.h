#pragma once

#include "Utils/FPoint.h"

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
};
