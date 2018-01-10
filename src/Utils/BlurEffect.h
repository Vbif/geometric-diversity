#pragma once

class BlurEffect {
public:
    BlurEffect();
    ~BlurEffect();

    void Begin();
    void End();

private:
    Render::Target* _original;
    Render::Target* _halfBlurred;
    Render::ShaderProgram* _shader;
};
