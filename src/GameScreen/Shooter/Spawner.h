#pragma once

#include "Enemy.h"
#include "Utils\Timer.h"

class Spawner {
public:
    Spawner();
    void SetPosition(const FPoint& center);
    void Restart(uint32_t toSpawn, float speed);
    void Draw();
    void Update(float dt, std::vector<Enemy>& toSpawn);

private:
    FPoint _spawnPoint;
    float _angle;
    Timer _timeForOne;
    uint32_t _remain;
    float _speed;
};
