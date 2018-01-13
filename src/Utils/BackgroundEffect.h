#pragma once

#include "Framework\ScreenObject.h"

class BackgroundEffect : public ScreenObject {
public:
    BackgroundEffect();
    ~BackgroundEffect();
    void Draw() override;
    void Update(float dt) override;

private:
    float _time;
    Render::ShaderProgram* _shader;
};
