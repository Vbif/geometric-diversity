#pragma once

#include "stdafx.h"

// TODO change to Render::PushMatrix
class MatrixLock {
public:
    MatrixLock()
    {
        Render::device.PushMatrix();
    }
    ~MatrixLock()
    {
        Render::device.PopMatrix();
    }

    void Translate(const FPoint& point)
    {
        Render::device.MatrixTranslate(point);
    }

    void Rotate(float angle)
    {
        Render::device.MatrixRotate(math::Vector3(0, 0, 1), angle * 180 / math::PI);
    }
};
