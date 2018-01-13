#pragma once

#include <array>
#include <memory>
#include <vector>

#include "Enemy.h"
#include "Gun.h"
#include "Spawner.h"

/// Игровое поле, содержащее все элементы игры
class Field : public ScreenObject {
public:
    Field(const FPoint& center, int size);
    void Restart(uint32_t enemyCount, float speed);
    void Draw();
    void Update(float dt);

    size_t TotalEnemyCount() const;
    size_t RemainEnemyCount() const;

private:
    std::array<FPoint, 4> _wallPoints;

    std::unique_ptr<Gun> _gun;
    std::vector<Enemy> _enemies;
    std::vector<Bullet> _bullets;

    uint32_t _enemyTotalCount;
    uint32_t _enemyKilled;
    Spawner _spawner;
};
