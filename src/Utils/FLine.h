#pragma once

#include "Utils\FPoint.h"

class FLine {
public:
    FPoint p0;
    FPoint p1;

public:
    FLine(const FPoint& begin, const FPoint& end)
        : p0(begin)
        , p1(end)
    {
    }
};
