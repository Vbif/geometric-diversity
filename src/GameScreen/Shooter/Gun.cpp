#include "stdafx.h"

#include "Gun.h"

Gun::Gun()
{
}

void Gun::Init(const FPoint& position, float gunSize)
{
    _center = position;
    _gunSize = gunSize;

    _wallPoints[0] = FPoint(0, gunSize / 2); // upper
    _wallPoints[1] = FPoint(gunSize / 2, 0); // right
    _wallPoints[2] = FPoint(0, -gunSize / 2); // bottom
    _wallPoints[3] = FPoint(-gunSize / 2, 0); // left

    for (auto& p : _wallPoints)
        p += _center;
}

void Gun::Draw()
{
    Render::DrawLine(_wallPoints[0], _wallPoints[1]);
    Render::DrawLine(_wallPoints[1], _wallPoints[2]);
    Render::DrawLine(_wallPoints[2], _wallPoints[3]);
    Render::DrawLine(_wallPoints[3], _wallPoints[0]);

    //float x, y;
    //_wallPoints[2].GetXY(x, y);
    //Render::DrawRotatedQuad(x, y, _gunSize / 2, _gunSize, -45);
}

void Gun::Update()
{
}
