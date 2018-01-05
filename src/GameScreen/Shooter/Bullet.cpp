#include "stdafx.h"

#include "Bullet.h"

static const float side = 20;

Bullet::Bullet(const FPoint& position, const FPoint& speed)
    : Transform(position, speed, side * math::sqrt(2))
{
}

void Bullet::Draw()
{
    Render::PushMatrix m;
    Render::device.MatrixTranslate(Position());

    const float halfSide = side / 2;
    Render::DrawRectWireframe(FRect(-halfSide, halfSide, -halfSide, halfSide));
}

void Bullet::Update(float dt)
{
    UpdateTransform(dt);
}
