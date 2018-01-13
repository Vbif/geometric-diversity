#pragma once

#include "FrameWork\GameWorld.h"

/// Патрон, вылетающий из пушки. Отскакивает от стен один раз и замедляется.
class Bullet : public GameObject {
public:
    class StartDraw {
    public:
        explicit StartDraw();

    private:
        Render::PushColor _color;
        Render::PushTexturing _tex;
    };

public:
    Bullet(const FPoint& position, const FPoint& speed);
    ~Bullet();
    void Draw() override;
    void Update(float dt) override;
    void OnCollision(GameObject& other) override;

private:
    uint32_t _collisionCount;
    ParticleEffectPtr _effect;
};
