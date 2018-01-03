#include "stdafx.h"

#include "FLine.h"

bool FLine::Intersects(const FLine& that, FPoint* targetPoint) const
{
    // TODO make for tunnel effect
    return false;
}

bool FLine::ClosestPointTo(const FPoint& point, FPoint* outPoint) const
{
    FPoint thisLine = AsVector();
    float len = thisLine.GetDistanceToOrigin();
    float dot = thisLine.GetDotProduct(point - p0) / math::sqr(len);

    FPoint res = p0 + dot * thisLine;

    if (!HavePointSimple(res))
        return false;

    if (outPoint)
        *outPoint = res;
    return true;
}

bool FLine::HavePoint(const FPoint& point) const
{
    float d0 = point.GetDistanceTo(p0);
    float d1 = point.GetDistanceTo(p1);
    float lineLen = p0.GetDistanceTo(p1);

    const float e = 1;
    float delta = d0 + d1 - lineLen;

    return std::abs(delta) < e;
}

bool FLine::HavePointSimple(const FPoint& point) const
{
    bool inX, inY;

    if (p0.x < p1.x)
        inX = point.x > p0.x && point.x < p1.x;
    else
        inX = point.x > p1.x && point.x < p0.x;

    if (p0.y < p1.y)
        inY = point.y > p0.y && point.y < p1.y;
    else
        inY = point.y > p1.y && point.y < p0.y;

    return inX && inY;
}
