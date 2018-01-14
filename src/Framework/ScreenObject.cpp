#include "stdafx.h"

#include "GameObject.h"
#include "ScreenObject.h"

void ScreenObject::Draw()
{
}

void ScreenObject::Update(float dt)
{
}

ScreenObject::~ScreenObject()
{
}

void ScreenObjectComposite::Draw()
{
    for (auto& o : _children)
        o->Draw();
}

void ScreenObjectComposite::Update(float dt)
{
    for (auto& o : _children)
        o->Update(dt);
}

void ScreenObjectComposite::AddChild(ScreenObject* child)
{
    _children.push_back(std::unique_ptr<ScreenObject>(child));
}
