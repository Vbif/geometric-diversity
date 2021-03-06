#include "stdafx.h"

#include "Bullet.h"
#include "Utils\EffectHolder.h"

static const float side = 10;

Bullet::StartDraw::StartDraw()
    : _color(NeonColors::Lilac)
    , _tex(false)
{
}

Bullet::Bullet(const FPoint& position, const FPoint& speed)
    : GameObject(position, speed, side * math::sqrt(2))
    , _collisionCount(0)
{
    _effect = EffectHolder::GetDefault()->AddEffect("plum", Position());
    SetTag("bullet");
}

Bullet::~Bullet()
{
    _effect->Kill();
}

void Bullet::Draw()
{
    StartDraw draw;
    Render::PushMatrix m;
    Render::device.MatrixTranslate(Position());
    float angle = Velocity().GetDirectedAngle(FPoint(0, 1));
    Render::device.MatrixRotate(math::Vector3::UnitZ, -angle * 180 / math::PI);

    const float halfSide = side / 2;
    Render::DrawWireframeRect(FRect(-halfSide, halfSide, -halfSide, halfSide), 3);
}

void Bullet::Update(float dt)
{
    GameObject::Update(dt);
    _effect->SetPos(Position());
}

void Bullet::OnCollision(GameObject& other)
{
    if (other.Tag() == "enemy") {
        Kill();
    } else if (other.Tag() == "level") {

        SetVelocity(Velocity() / 2);
        _collisionCount++;

        if (_collisionCount > 1) {
            Kill();
        };
    }
}
