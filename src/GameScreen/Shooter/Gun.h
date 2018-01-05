#pragma once

#include <array>

#include "Utils\FLine.h"

// �������, ���������� �� ����� �����.
class Gun {
public:
    Gun(const FPoint& position, float gunSize);
    void Draw();
    void Update(float dt);

    FLine GetLeftWall() const;
    FLine GetRightWall() const;

private:
    FPoint _center;
    float _gunSize;
    float _angle;

    std::array<FPoint, 4> _wallPoints;
};
