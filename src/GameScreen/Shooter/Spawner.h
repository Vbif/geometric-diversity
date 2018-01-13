#pragma once

#include "Enemy.h"
#include "Utils\Timer.h"

/// Объект, постепенно порождащий врагов
class Spawner : public ScreenObject {
public:
    Spawner();
    void SetPosition(const FPoint& center);
    void Restart(uint32_t toSpawn, float speed);
    void Draw() override;
    void Update(float dt) override;

private:
    FPoint _spawnPoint;
    float _angle;
    Timer _timeForOne;
    uint32_t _remain;
    float _speed;
};
