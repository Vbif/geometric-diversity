#pragma once

#include "ScreenObject.h"
#include "Utils\FCircle.h"

/// Описание положения игрового объекта в игровом поле
/// для простоты сделаем все объекты круглыми
class GameObject : public ScreenObject {
private:
    FPoint _position;
    FPoint _prevPosition;
    FPoint _velocity;
    float _bodyRadius;
    bool _isAlive;
    std::string _tag;

public:
    GameObject(const FPoint& position, const FPoint& velocity, float radius)
        : _position(position)
        , _prevPosition(position)
        , _velocity(velocity)
        , _bodyRadius(radius)
    {
        _isAlive = true;
    }

    void Update(float dt) override
    {
        _prevPosition = _position;
        _position += _velocity.Scaled(dt, dt);
    }

    virtual void OnCollision(GameObject& other)
    {
    }

    const FPoint& Position() const
    {
        return _position;
    }

    const FPoint& Velocity() const
    {
        return _velocity;
    }

    void SetVelocity(const FPoint& newValue)
    {
        _velocity = newValue;
    }

    FCircle GetBB() const
    {
        return FCircle(Position(), _bodyRadius);
    }

    FLine GetPath() const
    {
        return FLine(_prevPosition, _position);
    }

    void StepBack()
    {
        _position = _prevPosition;
    }

    void Stop()
    {
        _velocity = FPoint();
    }

    bool IsAlive() const
    {
        return _isAlive;
    }

    void Kill()
    {
        _isAlive = false;
    }

    const std::string& Tag() const
    {
        return _tag;
    }

    void SetTag(const std::string& tag)
    {
        _tag = tag;
    }
};
