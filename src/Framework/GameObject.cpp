#include "stdafx.h"

#include "GameObject.h"

GameObject::GameObject(const FPoint& position, const FPoint& velocity, float radius)
    : _position(position)
    , _prevPosition(position)
    , _velocity(velocity)
    , _bodyRadius(radius)
{
    _isAlive = true;
}

GameObject::~GameObject()
{
}

void GameObject::Draw()
{
}

void GameObject::Update(float dt)
{
    _prevPosition = _position;
    _position += _velocity.Scaled(dt, dt);
}

void GameObject::OnCollision(GameObject& other)
{
}

const FPoint& GameObject::Position() const
{
    return _position;
}

const FPoint& GameObject::Velocity() const
{
    return _velocity;
}

void GameObject::SetVelocity(const FPoint& newValue)
{
    _velocity = newValue;
}

FCircle GameObject::GetBB() const
{
    return FCircle(Position(), _bodyRadius);
}

FLine GameObject::GetPath() const
{
    return FLine(_prevPosition, _position);
}

void GameObject::StepBack()
{
    _position = _prevPosition;
}

void GameObject::Stop()
{
    _velocity = FPoint();
}

bool GameObject::IsAlive() const
{
    return _isAlive;
}

void GameObject::Kill()
{
    _isAlive = false;
}

const std::string& GameObject::Tag() const
{
    return _tag;
}

void GameObject::SetTag(const std::string& tag)
{
    _tag = tag;
}
