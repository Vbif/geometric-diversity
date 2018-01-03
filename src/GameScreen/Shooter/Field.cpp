#include "stdafx.h"

#include "Field.h"

#include "Utils\random.hpp"

Field::Field()
{
}

void Field::Init(const FPoint& center, int size)
{
    const float speed = 200;
    const size_t enemyCount = 10;

    // TODO combine with gun calc
    auto& upper = _wallPoints[0] = FPoint(0, size / 2);
    auto& right = _wallPoints[1] = FPoint(size / 2, 0);
    auto& bottom = _wallPoints[2] = FPoint(0, -size / 2);
    auto& left = _wallPoints[3] = FPoint(-size / 2, 0);

    for (auto& p : _wallPoints)
        p += center;

    const float gunSize = 100;
    _gun.Init(bottom + FPoint(0, gunSize / 2), gunSize);

    Enemy::StaticInit();

    // TODO make spawner with delta time between spawns
    auto spawnPoint = left + FPoint(100, 0);
    for (size_t i = 0; i < enemyCount; i++) {

        FPoint speedVector(speed, 0);
        speedVector.Rotate(math::random(-math::PI / 4, math::PI / 4));
        _enemies.push_back(Enemy(spawnPoint, speedVector));
    }
}

void Field::Draw()
{
    Render::device.SetTexturing(false);

    Render::DrawLine(_wallPoints[0], _wallPoints[1]);
    Render::DrawLine(_wallPoints[1], _wallPoints[2]);
    Render::DrawLine(_wallPoints[2], _wallPoints[3]);
    Render::DrawLine(_wallPoints[3], _wallPoints[0]);

    _gun.Draw();

    for (auto& enemy : _enemies)
        enemy.Draw();
}

void Field::Update(float dt)
{
    for (auto& enemy : _enemies)
        enemy.Update(dt);

    // resolve collision with walls
    std::array<FLine, 6> walls{
        _gun.GetLeftWall(),
        _gun.GetRightWall(),

        FLine(_wallPoints[0], _wallPoints[1]),
        FLine(_wallPoints[1], _wallPoints[2]),
        FLine(_wallPoints[2], _wallPoints[3]),
        FLine(_wallPoints[3], _wallPoints[0]),
    };

    for (auto& enemy : _enemies) {
        for (auto& wall : walls) {
            bool collision = TryResolveCollision(enemy, wall);
            if (collision)
                break;
        }
    }
}
