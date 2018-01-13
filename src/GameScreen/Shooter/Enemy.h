#pragma once

#include <array>

#include "FrameWork\GameWorld.h"

/// "Круглый" враг
class Enemy : public GameObject {
public:
    class StartDraw {
    public:
        explicit StartDraw();

    private:
        Render::PushColor _color;
        Render::PushTexturing _tex;
        Render::PushBlendMode _blend;
    };

public:
    static void StaticInit();

    Enemy(const FPoint& position, const FPoint& speed);
    void Draw() override;
    void Update(float dt) override;
    void OnCollision(GameObject& other) override;

private:
    static const size_t CircleQuality = 8;
    static std::array<FPoint, CircleQuality> _circlePoints;
    float _angle;
};
