#include "stdafx.h"

#include "Gun.h"

static const float bulletSpeed = 400;

Gun::Gun(const FPoint& position, float gunSize)
{
    _center = position;
    _gunSize = gunSize / math::sqrt(2);
    _angle = 0;
    _reloadTimer = Timer(1);

    _wallPoints[0] = FPoint(0, gunSize / 2); // upper
    _wallPoints[1] = FPoint(gunSize / 2, 0); // right
    _wallPoints[2] = FPoint(0, -gunSize / 2); // bottom
    _wallPoints[3] = FPoint(-gunSize / 2, 0); // left

    for (auto& p : _wallPoints)
        p += _center;

    _shotPosition = gunSize * 1.1;
}

void Gun::Draw()
{
    Render::PushTexturing t(false);
    Render::PushColor color(NeonColors::Blue);

    Render::DrawWireframeLine(_wallPoints[0], _wallPoints[1], 3);
    Render::DrawWireframeLine(_wallPoints[1], _wallPoints[2], 3);
    Render::DrawWireframeLine(_wallPoints[2], _wallPoints[3], 3);
    Render::DrawWireframeLine(_wallPoints[3], _wallPoints[0], 3);

    Render::PushMatrix m;
    Render::device.MatrixTranslate(_wallPoints[2]);
    Render::device.MatrixRotate(math::Vector3::UnitZ, _angle * 180 / math::PI);

    Render::DrawWireframeLine(FPoint(), FPoint(0, _gunSize), 15);
}

void Gun::Update(float dt, EffectsContainer& effectContainer, std::vector<Bullet>& toSpawn)
{
    FPoint mousePoint = Core::mainInput.GetMousePos();
    mousePoint = mousePoint - _wallPoints[2];

    // повернем пушку
    if (mousePoint.x != 0 && mousePoint.y != 0) {
        float angle = FPoint(0, 1).GetDirectedAngle(mousePoint);
        float maxAngle = (math::PI / 4) * 0.9;
        _angle = math::clamp(-maxAngle, maxAngle, angle);
    }

    _reloadTimer.Update(dt);
    // стрельнем, если вышел кулдаун
    if (Core::mainInput.GetMouseLeftButton() && _reloadTimer.IsExpired()) {
        _reloadTimer.Reset();

        auto position = FPoint(0, _shotPosition).Rotated(_angle) + _wallPoints[2];
        auto speed = FPoint(0, bulletSpeed).Rotated(_angle);

        toSpawn.emplace_back(position, speed, effectContainer);
    }
}

FLine Gun::GetLeftWall() const
{
    return FLine(_wallPoints[3], _wallPoints[0]);
}
FLine Gun::GetRightWall() const
{
    return FLine(_wallPoints[0], _wallPoints[1]);
}
