#pragma once

#include <array>

#include "Utils\FLine.h"

// TODO написать комментарии
class Gun {
public:
    Gun();
    void Init(const FPoint& position, float gunSize);
    void Draw();
    void Update();

    FLine GetLeftWall() const;
    FLine GetRightWall() const;

private:
    FPoint _center;
    float _gunSize;

    std::array<FPoint, 4> _wallPoints;
};
