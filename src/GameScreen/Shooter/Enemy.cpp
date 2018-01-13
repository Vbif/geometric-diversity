#include "stdafx.h"

#include <cmath>

#include "Enemy.h"
#include "Utils\EffectHolder.h"

static const float radius = 20;
std::array<FPoint, Enemy::CircleQuality> Enemy::_circlePoints;

void Enemy::StaticInit()
{
    float twoPi = math::PI * 2;

    for (size_t i = 0; i < _circlePoints.size(); i++) {
        float x = (radius * cos(i * twoPi / _circlePoints.size()));
        float y = (radius * sin(i * twoPi / _circlePoints.size()));
        _circlePoints[i] = FPoint(x, y);
    }
}

Enemy::StartDraw::StartDraw()
    : _color(NeonColors::Yellow)
    , _blend(BlendMode::Add)
    , _tex(false)
{
}

Enemy::Enemy(const FPoint& position, const FPoint& speed)
    : GameObject(position, speed, radius)
    , _angle(0)
{
    SetTag("enemy");
}

void Enemy::Draw()
{
    StartDraw draw;
    Render::PushMatrix m;
    Render::device.MatrixTranslate(Position());

    // показывает направление полета. для отладки.
    //Render::DrawLine(FPoint(0, 0), Velocity().Normalized() * radius);

    Render::device.MatrixRotate(math::Vector3::UnitZ, _angle);

    FPoint prev = _circlePoints.back();
    for (size_t i = 0; i < _circlePoints.size(); i++) {
        Render::DrawWireframeLine(prev, _circlePoints[i], 3);
        prev = _circlePoints[i];
    }
}

void Enemy::Update(float dt)
{
    GameObject::Update(dt);

    _angle += dt * 100;
    while (_angle > 360)
        _angle -= 360;
}

void Enemy::OnCollision(GameObject& other)
{
    if (other.Tag() == "bullet") {
        EffectHolder::GetDefault()->AddEffect("explosion", Position());
        MM::manager.PlaySample("explosion", false, 2);
        Kill();
    }
}
