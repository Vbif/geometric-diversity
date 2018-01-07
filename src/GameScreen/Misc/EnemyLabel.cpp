#include "stdafx.h"

#include "EnemyLabel.h"

EnemyLabel::EnemyLabel()
{
    SetValue(1, 1);
}

void EnemyLabel::SetPosition(const FPoint& textBegin, const FPoint& valueBegin)
{
    _text = textBegin;
    _value = valueBegin;
}

void EnemyLabel::Draw()
{
    size_t totalSize = 50;
    size_t currentSize = totalSize * _killedCount / _totalCount;
    size_t shift = 20;

    Render::device.SetTexturing(true);
    {
        Render::BindFont("arial");
        Render::PrintString(_text, "Killed:", 3.f, LeftAlign, BottomAlign);
    }

    Render::device.SetTexturing(false);
    {
        Render::PushMatrix m;

        Render::device.MatrixTranslate(_value);
        Render::DrawRect(IRect(0, 0, currentSize, currentSize));

        Render::device.MatrixTranslate(FPoint(totalSize + shift, 0));
        Render::DrawRect(IRect(0, 0, 1, totalSize));

        Render::device.MatrixTranslate(FPoint(shift, 0));
        Render::DrawRect(IRect(0, 0, totalSize, totalSize));
    }
}

void EnemyLabel::SetValue(size_t killed, size_t total)
{
    _killedCount = killed;
    _totalCount = total;
}
