#pragma once

class BackgroundEffect {
public:
    BackgroundEffect();
    ~BackgroundEffect();
    void Draw();
    void Update(float dt);

private:
    float _time;
    Render::ShaderProgram* _shader;
};
