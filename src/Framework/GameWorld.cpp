#include "stdafx.h"

#include "GameWorld.h"

GameWorld* GameWorld::_defaultGameWorld = nullptr;

template <class T>
void RemoveWithSwap(std::vector<T>& vector, typename std::vector<T>::iterator& i)
{
    size_t distance = std::distance(vector.begin(), i);
    if (i != vector.end() - 1)
        std::swap(*i, *(vector.end() - 1));

    vector.pop_back();
    i = vector.begin() + distance;
}

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

void GameWorld::RegisterRemoveCallback(const OnGameObjectRemove& callback)
{
    _removeCallbacks.push_back(callback);
}

void GameWorld::Clear(bool clearDynamic, bool clearStatic, bool clearCallbacks)
{
    if (clearDynamic)
        _dynamicBodies.clear();
    if (clearStatic)
        _staticGeometry.clear();
    if (clearCallbacks)
        _removeCallbacks.clear();
}

void GameWorld::Draw()
{
    for (auto& o : _dynamicBodies)
        o->Draw();
}

void GameWorld::Update(float dt)
{
    // TODO
    // fixed time staps with avoid spiral of death

    // подвинем все объекты
    for (auto& o : _dynamicBodies)
        o->Update(dt);

    for (size_t firstIt = 0; firstIt < _dynamicBodies.size(); firstIt++) {

        // откидываем мертвые объекты
        auto& first = GetDynamic(firstIt);
        if (!first.IsAlive())
            continue;

        for (size_t secondIt = firstIt + 1; secondIt < _dynamicBodies.size(); secondIt++) {

            // todo disable collision enemy x enemy

            // откидываем мертвые объекты
            auto& second = GetDynamic(secondIt);
            if (!second.IsAlive())
                continue;

            bool collision = CheckCollision(first, second);
            if (collision) {
                // игровые объекты не отскакивают друг от друга, поэтому просто вызовем коллбеки
                first.OnCollision(second);
                second.OnCollision(first);
            }

            // если первый объект умер, то больше с ним проверок не делаем
            if (!first.IsAlive())
                break;
        }
    }

    // удалим мертвые
    for (auto it = _dynamicBodies.begin(); it != _dynamicBodies.end();) {
        bool needIncrement = true;
        auto& object = *it->get();

        if (!object.IsAlive()) {
            needIncrement = false;
            DeleteRoutine(it);
        }

        if (needIncrement)
            ++it;
    }

    // отскочить от границ уровня
    GameObject level(FPoint(), FPoint(), 0);
    level.SetTag("level");
    for (auto it = _dynamicBodies.begin(); it != _dynamicBodies.end();) {

        bool needIncrement = true;
        auto& object = *it->get();

        for (auto& wall : _staticGeometry) {
            // столкнем
            bool collision = TryResolveCollision(object, wall);
            if (!collision)
                continue;

            // вызовем реакцию
            object.OnCollision(level);
            // если объект умер, сразу удалим его
            if (!object.IsAlive()) {
                needIncrement = false;
                DeleteRoutine(it);
            }

            break; // отбросим остальные
        }

        if (needIncrement)
            ++it;
    }
}

GameObject& GameWorld::GetDynamic(size_t i)
{
    return *_dynamicBodies[i].get();
}

FLine& GameWorld::GetStatic(size_t i)
{
    return _staticGeometry[i];
}

bool GameWorld::CheckCollision(GameObject& t0, GameObject& t1)
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

bool GameWorld::TryResolveCollision(GameObject& transform, const FLine& staticLine)
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

void GameWorld::DeleteRoutine(std::vector<std::unique_ptr<GameObject>>::iterator& it)
{
    for (auto& c : _removeCallbacks)
        c(*it->get());

    RemoveWithSwap(_dynamicBodies, it);
}
