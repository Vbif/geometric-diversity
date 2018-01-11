#include "stdafx.h"

#include "Transform.h"

bool CheckCollision(Transform& t0, Transform& t1)
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

bool TryResolveCollision(Transform& transform, const FLine& staticLine)
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
