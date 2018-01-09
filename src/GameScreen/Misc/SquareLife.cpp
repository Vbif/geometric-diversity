#include "stdafx.h"

#include "SquareLife.h"
#include "Utils\MatrixUtils.h"

SquareLife::SquareLife()
{
}

void SquareLife::Init(const FPoint& position, float size, const FRect& balloonPosition)
{
    _center = position;
    _size = size;

    // позиции точек относительно цента
    _frame = FRect(-size / 2, size / 2, -size / 2, size / 2);

    float eyeShiftX = size / 7;
    float eyeShiftY = size / 7;
    float eyeSize = size / 5;
    _eyes[0] = FRect(-eyeShiftX - eyeSize, -eyeShiftX, eyeShiftY, eyeShiftY + eyeSize);
    _eyes[1] = FRect(eyeShiftX, eyeShiftX + eyeSize, eyeShiftY, eyeShiftY + eyeSize);

    _balloon.reset(new Balloon(balloonPosition, position + _frame.LeftTop()));
}

void SquareLife::Draw()
{
    _balloon->Draw();

    Render::PushMatrix m;
    Render::device.MatrixTranslate(_center);
    Render::device.SetTexturing(false);

    Render::DrawRectWireframe(_frame);
    Render::DrawRectWireframe(_eyes[0]);
    Render::DrawRectWireframe(_eyes[1]);
}

void SquareLife::Update(float dt)
{
    _balloon->Update(dt);
}

Balloon& SquareLife::GetBalloon()
{
    return *_balloon;
}
