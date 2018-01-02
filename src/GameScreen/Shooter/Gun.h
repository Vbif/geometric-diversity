#pragma once

#include <array>

// TODO написать комментарии
class Gun {
public:
    Gun();
    void Init(const FPoint& position, float gunSize);
    void Draw();
    void Update();

private:
    FPoint _center;
    float _gunSize;

    std::array<FPoint, 4> _wallPoints;
};
