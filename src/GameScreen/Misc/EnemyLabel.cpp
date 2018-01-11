#include "stdafx.h"

#include "EnemyLabel.h"

EnemyLabel::EnemyLabel()
{
    _textCaption = codepage_to_utf8("Убито:", 1251);
    SetValue(1, 1);
}

void EnemyLabel::SetPosition(const FPoint& center)
{
    _textPosition = center;
}

void EnemyLabel::Draw()
{
    float scale = 1;

    Render::PushTexturing t0(true);
    {
        Render::BindFont("arial36");
        Render::PrintString(_textPosition, _textCaption, scale, RightAlign, CenterAlign);
    }

    float totalSize = Render::getFontHeight() * scale;
    float currentSize = totalSize * _killedCount / _totalCount;
    float shift = 20;

    Render::PushTexturing t1(false);
    {
        Render::PushMatrix m;

        Render::device.MatrixTranslate(_textPosition + FPoint(shift, 0));
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
