#pragma once

#include "ScreenObject.h"
#include "Utils\FCircle.h"

/// Описание положения игрового объекта в игровом поле
/// для простоты сделаем все объекты круглыми
class GameObject {
public:
    GameObject(const FPoint& position, const FPoint& velocity, float radius);
    virtual ~GameObject();

    virtual void Draw();
    virtual void Update(float dt);
    virtual void OnCollision(GameObject& other);

    const FPoint& Position() const;

    const FPoint& Velocity() const;
    void SetVelocity(const FPoint& newValue);

    FCircle GetBB() const;
    FLine GetPath() const;

    void StepBack();
    void Stop();

    bool IsAlive() const;

    void Kill();

    const std::string& Tag() const;
    void SetTag(const std::string& tag);

private:
    FPoint _position;
    FPoint _prevPosition;
    FPoint _velocity;
    float _bodyRadius;
    bool _isAlive;
    std::string _tag;
};
