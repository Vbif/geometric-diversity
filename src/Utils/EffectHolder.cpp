#include "stdafx.h"

#include "EffectHolder.h"

EffectHolder* EffectHolder::_default;

EffectsContainer* EffectHolder::GetDefault()
{
    assert(_default);
    return &_default->_effects;
}

EffectHolder::EffectHolder()
{
    _default = this;
}

EffectHolder::~EffectHolder()
{
    if (_default == this)
        _default = nullptr;
}

void EffectHolder::Draw()
{
    _effects.Draw();
}

void EffectHolder::Update(float dt)
{
    _effects.Update(dt);
}
