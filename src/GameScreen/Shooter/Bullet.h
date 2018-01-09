#pragma once

#include "Utils\Transform.h"

/// Патрон, вылетающий из пушки. Отскакивает от стен один раз и замедляется.
class Bullet : public Transform {
public:
    Bullet(const FPoint& position, const FPoint& speed);
    void Draw();
    void Update(float dt);
    bool OnCollision();

private:
    uint32_t _collisionCount;
};
