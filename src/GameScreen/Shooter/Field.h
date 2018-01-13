#pragma once

#include <array>
#include <memory>
#include <vector>

#include "Enemy.h"
#include "Gun.h"
#include "Spawner.h"

/// Игровое поле, содержащее все элементы игры
class Field : public ScreenObjectComposite {
public:
    Field(const FPoint& center, int size);
    void Restart(uint32_t enemyCount, float speed);
    void Draw() override;
    void Update(float dt) override;

    size_t TotalEnemyCount() const;
    size_t RemainEnemyCount() const;

private:
    void OnGameObjectRemoveFromWorld(GameObject& object);

private:
    std::array<FPoint, 4> _wallPoints;

    Gun* _gun;
    Spawner* _spawner;

    uint32_t _enemyTotalCount;
    uint32_t _enemyKilled;
};
