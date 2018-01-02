#pragma once

#include "stdafx.h"

namespace Render {

inline void DrawRectWireframe(const FRect& rect)
{
    std::array<FPoint, 4> points;
    points[0] = rect.LeftBottom();
    points[1] = rect.LeftTop();
    points[2] = rect.RightTop();
    points[3] = rect.RightBottom();

    FPoint prev = points.back();
    for (size_t i = 0; i < points.size(); i++) {
        Render::DrawLine(prev, points[i]);
        prev = points[i];
    }
}
}
