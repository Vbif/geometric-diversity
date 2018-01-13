#pragma once

#include "GameObject.h"

/// ������� ���. ������������ �������������� GameObject � ������ ��.
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
    // ����������� ������������ ������. �� �������� �� ���� ����. �� ������������.
    std::vector<FLine> _staticGeometry;
    // ������� �������, ����������� � ��������� �� ����� ����.
    std::vector<std::unique_ptr<GameObject>> _dynamicBodies;
};

bool CheckCollision(GameObject& t0, GameObject& t1);

bool TryResolveCollision(GameObject& transform, const FLine& staticLine);
