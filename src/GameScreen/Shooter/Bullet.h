#pragma once

#include "Utils\Transform.h"

/// ������, ���������� �� �����. ����������� �� ���� ���� ��� � �����������.
class Bullet : public Transform {
public:
    Bullet(const FPoint& position, const FPoint& speed);
    void Draw();
    void Update(float dt);
    bool OnCollision();

private:
    uint32_t _collisionCount;
};
