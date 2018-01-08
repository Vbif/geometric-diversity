#include "stdafx.h"

#include "Field.h"

#include "Utils\random.hpp"

const static size_t enemyCount = 1;

template <class T>
void remove_with_swap(std::vector<T>& vector, typename std::vector<T>::iterator& i)
{
    size_t distance = std::distance(vector.begin(), i);
    if (i != vector.end() - 1)
        std::swap(*i, *(vector.end() - 1));

    vector.pop_back();
    i = vector.begin() + distance;
}

Field::Field()
{
}

void Field::Init(const FPoint& center, int size)
{
    // TODO combine with gun calc
    auto& upper = _wallPoints[0] = FPoint(0, size / 2);
    auto& right = _wallPoints[1] = FPoint(size / 2, 0);
    auto& bottom = _wallPoints[2] = FPoint(0, -size / 2);
    auto& left = _wallPoints[3] = FPoint(-size / 2, 0);

    for (auto& p : _wallPoints)
        p += center;

    const float gunSize = 100;
    _gun.reset(new Gun(bottom + FPoint(0, gunSize / 2), gunSize));

    Enemy::StaticInit();
    _spawnPoint = left + FPoint(100, 0);
}

void Field::Restart()
{
    const float speed = 200;

    _enemies.clear();
    _bullets.clear();

    // TODO make spawner with delta time between spawns
    for (size_t i = 0; i < enemyCount; i++) {

        FPoint speedVector(speed, 0);
        speedVector.Rotate(math::random(-math::PI / 4, math::PI / 4));
        _enemies.push_back(Enemy(_spawnPoint, speedVector));
    }
}

void Field::Draw()
{
    Render::device.SetTexturing(false);

    Render::DrawLine(_wallPoints[0], _wallPoints[1]);
    Render::DrawLine(_wallPoints[1], _wallPoints[2]);
    Render::DrawLine(_wallPoints[2], _wallPoints[3]);
    Render::DrawLine(_wallPoints[3], _wallPoints[0]);

    _gun->Draw();

    for (auto& enemy : _enemies)
        enemy.Draw();

    for (auto& bullet : _bullets)
        bullet.Draw();
}

void Field::Update(float dt)
{
    _gun->Update(dt, _bullets);

    for (auto& enemy : _enemies)
        enemy.Update(dt);

    for (auto& bullet : _bullets)
        bullet.Update(dt);

    std::array<FLine, 6> walls{
        _gun->GetLeftWall(),
        _gun->GetRightWall(),

        FLine(_wallPoints[0], _wallPoints[1]),
        FLine(_wallPoints[1], _wallPoints[2]),
        FLine(_wallPoints[2], _wallPoints[3]),
        FLine(_wallPoints[3], _wallPoints[0]),
    };

    for (auto itEnemy = _enemies.begin(); itEnemy != _enemies.end();) {
        // отскочить от границ поля
        for (auto& wall : walls) {
            bool collision = TryResolveCollision(*itEnemy, wall);
            if (collision)
                break;
        }

        bool wasEnemyRemoved = false;
        // проверить столкновения с пулями
        for (auto itBullet = _bullets.begin(); itBullet != _bullets.end(); ++itBullet) {
            bool collision = CheckCollision(*itEnemy, *itBullet);
            if (collision) {
                wasEnemyRemoved = true;
                remove_with_swap(_enemies, itEnemy);
                remove_with_swap(_bullets, itBullet);
                // TODO Make explosion
                break;
            }
        }

        if (!wasEnemyRemoved)
            ++itEnemy;
    }
}

size_t Field::TotalEnemyCount() const
{
    return enemyCount;
}
size_t Field::RemainEnemyCount() const
{
    return _enemies.size();
}
