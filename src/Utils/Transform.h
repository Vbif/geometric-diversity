#pragma once

#include "Utils\FPoint.h"

/// Описание положения игрового объекта в игровом поле
class Transform {
private:
    FPoint _position;
    FPoint _prevPosition;
    FPoint _velocity;

public:
    Transform(const FPoint& position, const FPoint& velocity)
        : _position(position)
        , _prevPosition(position)
        , _velocity(velocity)
    {
    }

    Transform(const FPoint& position)
        : Transform(position, FPoint(0, 0))
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
};
