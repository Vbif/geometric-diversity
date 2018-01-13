#pragma once

#include "GameObject.h"

/// Игровой мир. Обрабатывает взаимодействие GameObject и рисует их.
class GameWorld : public ScreenObject {
public:
    static GameWorld* GetDefault();

    GameWorld();
    ~GameWorld();
    void SetAdDefault();

    void Add(GameObject* object);
    void Add(const FLine& object);

    void Draw() override;
    void Update(float dt) override;

private:
    static GameWorld* _defaultGameWorld;
    // Ограничения пространства уровня. не меняется по ходу игры. Не отображаются.
    std::vector<FLine> _staticGeometry;
    // Игровые объекты, добавляются и удаляются во время игры.
    std::vector<std::unique_ptr<GameObject>> _dynamicBodies;
};

bool CheckCollision(GameObject& t0, GameObject& t1);

bool TryResolveCollision(GameObject& transform, const FLine& staticLine);
