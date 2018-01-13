#pragma once

#include "Framework\ScreenObject.h"

class EffectHolder : public ScreenObject {
public:
    static EffectsContainer* GetDefault();
    EffectHolder();
    ~EffectHolder();
    void Draw() override;
    void Update(float dt) override;

private:
    static EffectHolder* _default;
    EffectsContainer _effects;
};
