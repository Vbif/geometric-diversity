#include "stdafx.h"

#include "Transform.h"

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

    // ������������ � ��������� �� ��������
    // TODO ������� ����� � ����� ������������
    transform.StepBack();

    // ������������� ������ ��������
    auto velocity = transform.Velocity();
    float angle = velocity.GetDirectedAngle(staticLine.AsVector());
    auto newVelocity = velocity.Rotated(2 * angle);

    transform.SetVelocity(newVelocity);

    return true;
}
