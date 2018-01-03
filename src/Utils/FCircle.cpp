#include "stdafx.h"

#include "FCircle.h"

bool FCircle::Intersects(const FLine& line, FPoint* targetPoint) const
{
    FPoint closest;
    bool onLine = line.ClosestPointTo(center, &closest);
    if (!onLine)
        return false;

    float distanceToPoint = closest.GetDistanceTo(center);
    if (distanceToPoint > radius)
        return false;

    if (targetPoint)
        *targetPoint = closest;
    return true;
}
