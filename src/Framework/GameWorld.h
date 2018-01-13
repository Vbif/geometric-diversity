#pragma once

#include <functional>

#include "GameObject.h"

/// Игровой мир. Обрабатывает взаимодействие GameObject и рисует их.
class GameWorld : public ScreenObject {
public:
    using OnGameObjectRemove = std::function<void(GameObject& wasKilled)>;

public:
    static GameWorld* GetDefault();

    GameWorld();
    ~GameWorld();
    void SetAdDefault();

    void Add(GameObject* object);
    void Add(const FLine& object);
    void RegisterRemoveCallback(const OnGameObjectRemove& callback);
    void Clear(bool clearDynamic, bool clearStatic, bool clearCallbacks);

    void Draw() override;
    void Update(float dt) override;

private:
    GameObject& GetDynamic(size_t i);
    FLine& GetStatic(size_t i);
    bool CheckCollision(GameObject& t0, GameObject& t1);
    bool TryResolveCollision(GameObject& transform, const FLine& staticLine);
    void DeleteRoutine(std::vector<std::unique_ptr<GameObject>>::iterator& it);

private:
    static GameWorld* _defaultGameWorld;
    // Ограничения пространства уровня. не меняется по ходу игры. Не отображаются.
    std::vector<FLine> _staticGeometry;
    // Игровые объекты, добавляются и удаляются во время игры.
    std::vector<std::unique_ptr<GameObject>> _dynamicBodies;
    // Коллбеки для оповещения других объектов.
    std::vector<OnGameObjectRemove> _removeCallbacks;
};
