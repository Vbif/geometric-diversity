#include "stdafx.h"

#include "TimeLabel.h"

TimeLabel::TimeLabel()
{
    _textCaption = codepage_to_utf8("Время:", 1251);
    SetValue(1, 1);
}

void TimeLabel::SetPosition(const FPoint& center)
{
    _textPosition = center;
}

void TimeLabel::Draw()
{
    float scale = 1;

    Render::device.SetTexturing(true);
    {
        Render::BindFont("arial36");
        Render::PrintString(_textPosition, _textCaption, scale, RightAlign, CenterAlign);
    }

    float totalSize = Render::getFontHeight() * scale;
    float currentSize = totalSize * _time / _total;
    float shift = 20;

    Render::device.SetTexturing(false);
    {
        Render::PushMatrix m;

        float s = currentSize / 2;
        Render::device.MatrixTranslate(_textPosition + FPoint(shift + s, 0));
        Render::DrawRect(IRect(-s, -s, currentSize, currentSize));
    }
}

void TimeLabel::SetValue(uint32_t remain, uint32_t total)
{
    _time = remain;
    _total = total;
}
