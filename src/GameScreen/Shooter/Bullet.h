#pragma once

#include "Utils\Transform.h"

/// Патрон, вылетающий из пушки
class Bullet : public Transform {
public:
    Bullet(const FPoint& position, const FPoint& speed);
    void Draw();
    void Update(float dt);

private:
};
