#pragma once

#include "Utils\Transform.h"

/// ������, ���������� �� �����
class Bullet : public Transform {
public:
    Bullet(const FPoint& position, const FPoint& speed);
    void Draw();
    void Update(float dt);

private:
};
