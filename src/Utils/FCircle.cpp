#include "stdafx.h"

#include "FCircle.h"

bool FCircle::Intersects(const FLine& line, FPoint* targetPoint) const
{
    auto closest = line.ClosestPointTo(center);
    if (closest.GetDistanceTo(center) <= radius) {
        if (targetPoint)
            *targetPoint = closest;
        return true;
    }
    return false;
}
