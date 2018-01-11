#pragma once

#include <array>

#include "Utils\FLine.h"
#include "Utils\Timer.h"

#include "Bullet.h"

/// “уррель, стрел€юща€ по клику мышки.
class Gun {
public:
    Gun(const FPoint& position, float gunSize);
    void Draw();
    void Update(float dt, EffectsContainer& effectContainer, std::vector<Bullet>& toSpawn);

    FLine GetLeftWall() const;
    FLine GetRightWall() const;

private:
    FPoint _center;
    float _gunSize;
    float _angle;
    Timer _reloadTimer;
    float _shotPosition;

    std::array<FPoint, 4> _wallPoints;
};
