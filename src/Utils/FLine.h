#pragma once

#include "Utils\FPoint.h"

/// Класс для работы с линиями
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

    FPoint AsVector() const
    {
        return p1 - p0;
    }

    bool Intersects(const FLine& that, FPoint* targetPoint) const;
    bool ClosestPointTo(const FPoint& point, FPoint* outPoint) const;
    bool HavePoint(const FPoint& point) const;

private:
    bool FLine::HavePointSimple(const FPoint& point) const;
};
