#include "stdafx.h"

#include "EnemyLabel.h"

EnemyLabel::EnemyLabel()
{
    SetValue(1, 1);
}

void EnemyLabel::SetPosition(const FPoint& center)
{
    _text = center;
}

void EnemyLabel::Draw()
{
    float scale = 3;

    Render::device.SetTexturing(true);
    {
        Render::BindFont("arial");
        Render::PrintString(_text, "Killed:", scale, RightAlign, CenterAlign);
    }

    float totalSize = Render::getFontHeight() * scale;
    float currentSize = totalSize * _killedCount / _totalCount;
    float shift = 20;

    Render::device.SetTexturing(false);
    {
        Render::PushMatrix m;

        Render::device.MatrixTranslate(_text + FPoint(shift, 0));
        Render::DrawRect(IRect((totalSize - currentSize) / 2, -currentSize / 2, currentSize, currentSize));

        Render::device.MatrixTranslate(FPoint(totalSize + shift, 0));
        Render::DrawRect(IRect(0, -totalSize / 2, 1, totalSize));

        Render::device.MatrixTranslate(FPoint(shift, 0));
        Render::DrawRect(IRect(0, -totalSize / 2, totalSize, totalSize));
    }
}

void EnemyLabel::SetValue(size_t killed, size_t total)
{
    _killedCount = killed;
    _totalCount = total;
}
