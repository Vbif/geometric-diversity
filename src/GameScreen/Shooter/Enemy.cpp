#include "stdafx.h"

#include <cmath>

#include "Enemy.h"
#include "Utils\MatrixUtils.h"

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
    : Transform(position, speed, radius)
{
}

void Enemy::Draw()
{
    MatrixLock m;
    m.Translate(Position());

    // TODO for debug
    Render::DrawLine(FPoint(0, 0), Velocity().Normalized() * radius);

    // TODO Rotate enemy

    FPoint prev = _circlePoints.back();
    for (size_t i = 0; i < _circlePoints.size(); i++) {
        Render::DrawLine(prev, _circlePoints[i]);
        prev = _circlePoints[i];
    }
}

void Enemy::Update(float dt)
{
    UpdateTransform(dt);
}
