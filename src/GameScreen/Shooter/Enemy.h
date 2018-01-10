#pragma once

#include <array>

#include "Utils\FCircle.h"
#include "Utils\Transform.h"

// "Круглый" враг
class Enemy : public Transform {
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
    void Draw();
    void Update(float dt);

private:
    static const size_t CircleQuality = 8;
    static std::array<FPoint, CircleQuality> _circlePoints;
};
