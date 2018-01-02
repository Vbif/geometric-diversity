#pragma once

#include "stdafx.h"

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
};
