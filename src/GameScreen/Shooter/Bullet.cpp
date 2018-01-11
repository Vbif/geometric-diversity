#include "stdafx.h"

#include "Bullet.h"

static const float side = 10;

Bullet::StartDraw::StartDraw()
    : _color(NeonColors::Lilac)
    , _tex(false)
{
}

Bullet::Bullet(const FPoint& position, const FPoint& speed, EffectsContainer& effectContainer)
    : Transform(position, speed, side * math::sqrt(2))
    , _collisionCount(0)
{
    _effect = effectContainer.AddEffect("plum", Position());
}

Bullet::~Bullet()
{
    _effect->Kill();
}

void Bullet::Draw()
{
    Render::PushMatrix m;
    Render::device.MatrixTranslate(Position());
    float angle = Velocity().GetDirectedAngle(FPoint(0, 1));
    Render::device.MatrixRotate(math::Vector3::UnitZ, -angle * 180 / math::PI);

    const float halfSide = side / 2;
    Render::DrawWireframeRect(FRect(-halfSide, halfSide, -halfSide, halfSide), 3);
}

void Bullet::Update(float dt)
{
    UpdateTransform(dt);
    _effect->SetPos(Position());
}

bool Bullet::OnCollision()
{
    SetVelocity(Velocity() / 2);
    _collisionCount++;

    if (_collisionCount > 1) {
        return true;
    };
    return false;
}
