#pragma once

#include <array>

// TODO написать комментарии
class Enemy {
public:
    static void StaticInit();
    Enemy();
    void Init(const FPoint& position);
    void Draw();
    void Update();

private:
    static const size_t CircleQuality = 8;
    static std::array<FPoint, CircleQuality> _circlePoints;

    FPoint _center;
};
