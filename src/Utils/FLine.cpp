#include "stdafx.h"

#include "FLine.h"

bool FLine::Intersects(const FLine& that, FPoint* targetPoint) const
{
    return false;
}

FPoint FLine::ClosestPointTo(const FPoint& point) const
{
    float A1 = p1.y - p0.y;
    float B1 = p1.x - p0.x;
    float C1 = (p1.y - p0.y) * p0.x + (p1.x - p0.x) * p0.y;
    float C2 = -B1 * point.x + A1 * point.y;
    float det = A1 * A1 - -B1 * B1;
    float cx = 0;
    float cy = 0;
    if (det != 0) {
        cx = (A1 * C1 - B1 * C2) / det;
        cy = (A1 * C2 - -B1 * C1) / det;
    } else {
        cx = point.x;
        cy = point.y;
    }
    return FPoint(cx, cy);
}
