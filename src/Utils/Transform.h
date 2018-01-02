#pragma once

#include "Utils\FCircle.h"

/// Описание положения игрового объекта в игровом поле
/// для простоты сделаем все объекты круглыми
class Transform {
private:
    FPoint _position;
    FPoint _prevPosition;
    FPoint _velocity;
    float _bodyRadius;

public:
    Transform(const FPoint& position, const FPoint& velocity, float radius)
        : _position(position)
        , _prevPosition(position)
        , _velocity(velocity)
        , _bodyRadius(radius)
    {
    }

    void UpdateTransform(float dt)
    {
        _prevPosition = _position;
        _position += _velocity.Scaled(dt, dt);
    }

    const FPoint& Position() const
    {
        return _position;
    }

    FCircle GetBB() const
    {
        return FCircle(Position(), _bodyRadius);
    }

    void ReverseVelocity()
    {
        _velocity = -_velocity;
    }
};

bool TryResolveCollision(Transform& transform, const FLine& staticLine);
