#include "stdafx.h"

#include "Field.h"
#include "Utils\EffectHolder.h"

Field::Field(const FPoint& center, int size)
{
    auto& upper = _wallPoints[0] = FPoint(0, size / 2);
    auto& right = _wallPoints[1] = FPoint(size / 2, 0);
    auto& bottom = _wallPoints[2] = FPoint(0, -size / 2);
    auto& left = _wallPoints[3] = FPoint(-size / 2, 0);

    for (auto& p : _wallPoints)
        p += center;

    const float gunSize = 100;
    _gun = new Gun(bottom + FPoint(0, gunSize / 2), gunSize);
    AddChild(_gun);

    _spawner = new Spawner();
    _spawner->SetPosition(left + FPoint(50, 0));
    AddChild(_spawner);

    // заполним границы уровня
    auto world = GameWorld::GetDefault();
    world->Add(FLine(_wallPoints[0], _wallPoints[1]));
    world->Add(FLine(_wallPoints[1], _wallPoints[2]));
    world->Add(FLine(_wallPoints[2], _wallPoints[3]));
    world->Add(FLine(_wallPoints[3], _wallPoints[0]));

    world->Add(_gun->GetLeftWall());
    world->Add(_gun->GetRightWall());

    world->RegisterRemoveCallback(
        [this](auto& c) {
            OnGameObjectRemoveFromWorld(c);
        });
}

void Field::Restart(uint32_t enemyCount, float speed)
{
    _enemyTotalCount = enemyCount;
    _enemyKilled = 0;

    _spawner->Restart(enemyCount, speed);
}

void Field::Draw()
{
    {
        Render::PushTexturing t(false);
        Render::PushColor color(NeonColors::Blue);

        Render::DrawWireframeLine(_wallPoints[0], _wallPoints[1], 5);
        Render::DrawWireframeLine(_wallPoints[1], _wallPoints[2], 5);
        Render::DrawWireframeLine(_wallPoints[2], _wallPoints[3], 5);
        Render::DrawWireframeLine(_wallPoints[3], _wallPoints[0], 5);
    }

    ScreenObjectComposite::Draw();
}

void Field::Update(float dt)
{
    ScreenObjectComposite::Update(dt);
}

size_t Field::TotalEnemyCount() const
{
    return _enemyTotalCount;
}

size_t Field::RemainEnemyCount() const
{
    return _enemyTotalCount - _enemyKilled;
}

void Field::OnGameObjectRemoveFromWorld(GameObject& object)
{
    if (object.Tag() == "enemy") {
        _enemyKilled++;
    }
}
