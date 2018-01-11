#include "stdafx.h"

#include "Spawner.h"

Spawner::Spawner()
    : _timeForOne(0.5)
{
}

void Spawner::SetPosition(const FPoint& center)
{
    _spawnPoint = center;
}

void Spawner::Restart(uint32_t toSpawn, float speed)
{
    _angle = 0;
    _remain = toSpawn;
    _speed = speed;
    _timeForOne.Reset();
}

void Spawner::Draw()
{
    if (_remain == 0)
        return;

    Render::PushTexturing t(false);
    Render::PushMatrix m;
    Render::device.MatrixTranslate(_spawnPoint);
    Render::device.MatrixRotate(math::Vector3::UnitZ, _angle);

    float size = 20;
    Render::DrawRect(-size / 2, -size / 2, size, size);
}

void Spawner::Update(float dt, std::vector<Enemy>& toSpawn)
{
    if (_remain == 0)
        return;

    _angle += dt * 400;
    while (_angle > 360)
        _angle -= 360;

    _timeForOne.Update(dt);

    if (_timeForOne.IsExpired()) {
        _timeForOne.Reset();
        _remain--;

        FPoint speedVector(_speed, 0);
        speedVector.Rotate(math::random(-math::PI / 4, math::PI / 4));
        toSpawn.push_back(Enemy(_spawnPoint, speedVector));

        MM::manager.PlaySample("born", false, 0.2f);
    }
}
