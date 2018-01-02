#include "stdafx.h"

#include "Transform.h"

bool TryResolveCollision(Transform& transform, const FLine& staticLine)
{
    bool collision = transform.GetBB().Intersects(staticLine, nullptr);
    if (!collision) {
        return false;
    }

    transform.ReverseVelocity(); // mock
    return true;
}
