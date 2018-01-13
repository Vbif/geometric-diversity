#include "stdafx.h"

#include "GameWorld.h"

GameWorld* GameWorld::_defaultGameWorld = nullptr;

GameWorld* GameWorld::GetDefault()
{
    return _defaultGameWorld;
}

GameWorld::GameWorld()
{
}

GameWorld::~GameWorld()
{
    if (this == _defaultGameWorld)
        _defaultGameWorld = nullptr;
}

void GameWorld::SetAdDefault()
{
    delete _defaultGameWorld;
    _defaultGameWorld = this;
}

void GameWorld::Add(GameObject* object)
{
    _dynamicBodies.emplace_back(object);
}

void GameWorld::Add(const FLine& object)
{
    _staticGeometry.emplace_back(object);
}

void GameWorld::Draw()
{
    for (auto& o : _dynamicBodies)
        o->Draw();
}

void GameWorld::Update(float dt)
{
    // подвинем все объекты
    for (auto& o : _dynamicBodies)
        o->Update(dt);

    //for (auto itEnemy = _dynamicBodies.begin(); itEnemy != _dynamicBodies.end();) {
    //	// отскочить от границ поля
    //	for (auto& wall : _staticGeometry) {
    //		bool collision = TryResolveCollision(*itEnemy, wall);
    //		if (collision)
    //			break;
    //	}

    //	bool wasEnemyRemoved = false;
    //	// проверить столкновения с пулями
    //	for (auto itBullet = _bullets.begin(); itBullet != _bullets.end(); ++itBullet) {
    //		bool collision = CheckCollision(*itEnemy, *itBullet);
    //		if (collision) {
    //			_effects.AddEffect("explosion", itEnemy->Position());
    //			MM::manager.PlaySample("explosion", false, 2);

    //			remove_with_swap(_enemies, itEnemy);
    //			remove_with_swap(_bullets, itBullet);
    //			wasEnemyRemoved = true;

    //			_enemyKilled++;
    //			break;
    //		}
    //	}

    //	if (!wasEnemyRemoved)
    //		++itEnemy;
    //}

    //for (auto itBullet = _bullets.begin(); itBullet != _bullets.end();) {

    //	bool wasBulletRemoved = false;

    //	// отскочить от границ поля
    //	for (auto& wall : walls) {
    //		bool collision = TryResolveCollision(*itBullet, wall);
    //		if (!collision)
    //			continue;

    //		bool needRemove = itBullet->OnCollision();
    //		if (needRemove) {
    //			remove_with_swap(_bullets, itBullet);
    //			wasBulletRemoved = true;
    //		}
    //		break;
    //	}

    //	if (!wasBulletRemoved)
    //		++itBullet;
    //}
}

bool CheckCollision(GameObject& t0, GameObject& t1)
{
    auto bb0 = t0.GetBB();
    auto bb1 = t1.GetBB();

    auto path0 = t0.GetPath();
    auto path1 = t1.GetPath();

    if (bb0.Intersects(bb1))
        return true;
    if (path0.Intersects(path1, nullptr))
        return true;

    return false;
}

bool TryResolveCollision(GameObject& transform, const FLine& staticLine)
{
    auto bb = transform.GetBB();
    auto path = transform.GetPath();

    FPoint intersectPoint, tunnelPoint;
    bool collisionIntersect = bb.Intersects(staticLine, &intersectPoint);
    bool collisionTunnel = path.Intersects(staticLine, &tunnelPoint);

    if (!collisionIntersect && !collisionTunnel) {
        return false;
    }

    // откатываемся в состояние до коллизии
    transform.StepBack();

    // разворачиваем вектор скорости
    auto velocity = transform.Velocity();
    float angle = velocity.GetDirectedAngle(staticLine.AsVector());
    auto newVelocity = velocity.Rotated(2 * angle);

    transform.SetVelocity(newVelocity);

    return true;
}
