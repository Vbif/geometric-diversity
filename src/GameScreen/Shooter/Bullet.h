#pragma once

#include "Utils\Transform.h"

/// ������, ���������� �� �����. ����������� �� ���� ���� ��� � �����������.
class Bullet : public Transform {
public:
    class StartDraw {
    public:
        explicit StartDraw();

    private:
        Render::PushColor _color;
        Render::PushTexturing _tex;
    };

public:
    Bullet(const FPoint& position, const FPoint& speed, EffectsContainer& effectContainer);
    ~Bullet();
    void Draw();
    void Update(float dt);
    bool OnCollision();

private:
    uint32_t _collisionCount;
    ParticleEffectPtr _effect;
};
