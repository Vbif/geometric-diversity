#include "stdafx.h"

#include <cmath>

#include "Enemy.h"
#include "Utils\MatrixUtils.h"

std::array<FPoint, Enemy::CircleQuality> Enemy::_circlePoints;

void Enemy::StaticInit()
{
    float radius = 20;
    float twoPi = math::PI * 2;

    for (size_t i = 0; i < _circlePoints.size(); i++) {
        float x = (radius * cos(i * twoPi / _circlePoints.size()));
        float y = (radius * sin(i * twoPi / _circlePoints.size()));
        _circlePoints[i] = FPoint(x, y);
    }
}

Enemy::Enemy()
{
}

void Enemy::Init(const FPoint& position)
{
    _center = position;
}

void Enemy::Draw()
{
    MatrixLock m;
    m.Translate(_center);
    // TODO Rotate enemy

    FPoint prev = _circlePoints.back();
    for (size_t i = 0; i < _circlePoints.size(); i++) {
        Render::DrawLine(prev, _circlePoints[i]);
        prev = _circlePoints[i];
    }
}

void Enemy::Update()
{
}
