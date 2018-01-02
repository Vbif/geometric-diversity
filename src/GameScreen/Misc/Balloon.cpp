#include "stdafx.h"

#include "Balloon.h"

Balloon::Balloon(const FRect& mainPosition, const FPoint& firstPoint)
{
    _mainBallon = mainPosition;

    auto mainLeft = _mainBallon.LeftBottom();
    auto mainRight = _mainBallon.RightBottom();

    auto mainClosest = firstPoint.GetDistanceTo(mainLeft) < firstPoint.GetDistanceTo(mainRight)
        ? mainLeft
        : mainRight;

    float sizes[3] = { 10, 20, 30 };
    float xdelta = (mainClosest - firstPoint).x / _targetBallons.size();

    for (size_t i = 0; i < _targetBallons.size(); i++) {

        float x = firstPoint.x + xdelta * i;
        float y = firstPoint.y - math::log2(0.1f + 0.33f * i);
        _targetBallons[i] = FRect(x, x + sizes[i], y, y + sizes[i]);
    }
}

void Balloon::Draw()
{
    Render::DrawRectWireframe(_mainBallon);

    for (auto& r : _targetBallons)
        Render::DrawRectWireframe(r);
}

void Balloon::Update()
{
}
