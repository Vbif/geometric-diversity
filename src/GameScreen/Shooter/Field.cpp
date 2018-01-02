#include "stdafx.h"

#include "Field.h"

Field::Field()
{
}

void Field::Init(const FPoint& center, int size)
{
    // TODO combine with gun calc
    _wallPoints[0] = FPoint(0, size / 2); // upper
    _wallPoints[1] = FPoint(size / 2, 0); // right
    _wallPoints[2] = FPoint(0, -size / 2); // bottom
    _wallPoints[3] = FPoint(-size / 2, 0); // left

    for (auto& p : _wallPoints)
        p += center;

    const float gunSize = 100;
    _gun.Init(_wallPoints[2] + FPoint(0, gunSize / 2), gunSize);

    Enemy::StaticInit();
    for (size_t i = 0; i < 10; i++) {
        _enemies.push_back(Enemy());
        _enemies.back().Init(FPoint(center));
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
}
