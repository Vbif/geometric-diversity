#pragma once

#include <functional>

#include "GameObject.h"

/// ������� ���. ������������ �������������� GameObject � ������ ��.
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
    void UpdateInternal(float dt);
    GameObject& GetDynamic(size_t i);
    FLine& GetStatic(size_t i);
    bool CheckCollision(GameObject& t0, GameObject& t1);
    float ResolveCollisionProbe(GameObject& transform, const FLine& staticLine);
    void ResolveCollision(GameObject& transform, const FLine& staticLine);
    void DeleteRoutine(std::vector<std::unique_ptr<GameObject>>::iterator& it);

private:
    static GameWorld* _defaultGameWorld;
    // ����������� ������������ ������. �� �������� �� ���� ����. �� ������������.
    std::vector<FLine> _staticGeometry;
    // ������� �������, ����������� � ��������� �� ����� ����.
    std::vector<std::unique_ptr<GameObject>> _dynamicBodies;
    // �������� ��� ���������� ������ ��������.
    std::vector<OnGameObjectRemove> _removeCallbacks;
    // ���������� �� ����������� ��������. �������� � ������, ��� �� �������� ���������.
    std::vector<std::pair<size_t, float>> _distances;
    // ���������� ����� �� ���������� �������
    float _timeRemain;
};
