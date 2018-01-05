#include "stdafx.h"

#include "Gun.h"

Gun::Gun(const FPoint& position, float gunSize)
{
    _center = position;
    _gunSize = gunSize / math::sqrt(2);
    _angle = 0;

    _wallPoints[0] = FPoint(0, gunSize / 2); // upper
    _wallPoints[1] = FPoint(gunSize / 2, 0); // right
    _wallPoints[2] = FPoint(0, -gunSize / 2); // bottom
    _wallPoints[3] = FPoint(-gunSize / 2, 0); // left

    for (auto& p : _wallPoints)
        p += _center;
}

void Gun::Draw()
{
    Render::DrawLine(_wallPoints[0], _wallPoints[1]);
    Render::DrawLine(_wallPoints[1], _wallPoints[2]);
    Render::DrawLine(_wallPoints[2], _wallPoints[3]);
    Render::DrawLine(_wallPoints[3], _wallPoints[0]);

    MatrixLock m;
    m.Translate(_wallPoints[2]);
    m.Rotate(_angle);

    Render::DrawLine(FPoint(), FPoint(0, _gunSize));
}

void Gun::Update(float dt)
{
    FPoint mousePoint = Core::mainInput.GetMousePos();
    mousePoint = mousePoint - _wallPoints[2];
    if (mousePoint.x == 0 || mousePoint.y == 0)
        return;

    float angle = FPoint(0, 1).GetDirectedAngle(mousePoint);

    float maxAngle = (math::PI / 4) * 0.9;
    _angle = math::clamp(-maxAngle, maxAngle, angle);
}

FLine Gun::GetLeftWall() const
{
    return FLine(_wallPoints[3], _wallPoints[0]);
}
FLine Gun::GetRightWall() const
{
    return FLine(_wallPoints[0], _wallPoints[1]);
}
