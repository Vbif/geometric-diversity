#include "stdafx.h"

#include "Bullet.h"

static const float side = 10;

Bullet::Bullet(const FPoint& position, const FPoint& speed)
    : Transform(position, speed, side * math::sqrt(2))
    , _collisionCount(0)
{
}

void Bullet::Draw()
{
    Render::PushMatrix m;
    Render::device.MatrixTranslate(Position());
    float angle = Velocity().GetDirectedAngle(FPoint(0, 1));
    Render::device.MatrixRotate(math::Vector3::UnitZ, -angle * 180 / math::PI);

    const float halfSide = side / 2;
    Render::DrawRectWireframe(FRect(-halfSide, halfSide, -halfSide, halfSide));
}

void Bullet::Update(float dt)
{
    UpdateTransform(dt);
}

bool Bullet::OnCollision()
{
    SetVelocity(Velocity() / 2);
    _collisionCount++;

    return _collisionCount > 1;
}
