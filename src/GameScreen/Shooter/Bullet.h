#pragma once

#include "FrameWork\GameWorld.h"

/// ������, ���������� �� �����. ����������� �� ���� ���� ��� � �����������.
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
    void Draw();
    void Update(float dt);
    bool OnCollision();

private:
    uint32_t _collisionCount;
    ParticleEffectPtr _effect;
};
