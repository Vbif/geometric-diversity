#include "stdafx.h"

#include "SquareLife.h"

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

    auto closestSide = balloonPosition.CenterPoint().x < position.x ? _frame.LeftTop() : _frame.RightTop();
    _balloon.reset(new Balloon(balloonPosition, position + closestSide));
}

void SquareLife::Draw()
{
    _balloon->Draw();

    Render::PushTexturing t(false);
    Render::PushMatrix m;
    Render::device.MatrixTranslate(_center);

    Render::DrawWireframeRect(_frame, 4);
    Render::DrawWireframeRect(_eyes[0], 2);
    Render::DrawWireframeRect(_eyes[1], 2);
}

void SquareLife::Update(float dt)
{
    _balloon->Update(dt);

    if (_callback && _balloon->IsInactive()) {
        auto copy = std::move(_callback);
        _callback = nullptr;
        copy();
    }
}

void SquareLife::Say(const std::string& text, const SayCallback& callback)
{
    _callback = callback;
    _balloon->Show(text);
}
