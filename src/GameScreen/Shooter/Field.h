#pragma once

#include <array>
#include <vector>

#include "Enemy.h"
#include "Gun.h"

// TODO написать комментарии
class Field {
public:
    Field();
    void Init(const FPoint& center, int size);
    void Draw();
    void Update(float dt);

private:
    std::array<FPoint, 4> _wallPoints;

    Gun _gun;
    std::vector<Enemy> _enemies;
};
