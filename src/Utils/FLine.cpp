#include "stdafx.h"

#include "FLine.h"

bool FLine::Intersects(const FLine& that, FPoint* targetPoint) const
{
    float x1 = this->p0.x;
    float y1 = this->p0.y;
    float x2 = this->p1.x;
    float y2 = this->p1.y;

    float x3 = that.p0.x;
    float y3 = that.p0.y;
    float x4 = that.p1.x;
    float y4 = that.p1.y;

    float uA = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
    float uB = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));

    if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) {

        float intersectionX = x1 + (uA * (x2 - x1));
        float intersectionY = y1 + (uA * (y2 - y1));

        if (targetPoint)
            *targetPoint = FPoint(intersectionX, intersectionY);

        return true;
    }
    return false;
}

bool FLine::ClosestPointTo(const FPoint& point, FPoint* outPoint) const
{
    FPoint thisLine = AsVector();
    float len = thisLine.GetDistanceToOrigin();
    float dot = thisLine.GetDotProduct(point - p0) / math::sqr(len);

    FPoint res = p0 + dot * thisLine;

    if (!HavePointSimple(res)) {

        float len0 = point.GetDistanceTo(p0);
        float len1 = point.GetDistanceTo(p1);

        if (outPoint)
            if (len0 < len1)
                *outPoint = p0;
            else
                *outPoint = p1;

        return true;
    }

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
        inX = point.x >= p0.x && point.x <= p1.x;
    else
        inX = point.x >= p1.x && point.x <= p0.x;

    if (p0.y < p1.y)
        inY = point.y >= p0.y && point.y <= p1.y;
    else
        inY = point.y >= p1.y && point.y <= p0.y;

    return inX && inY;
}
