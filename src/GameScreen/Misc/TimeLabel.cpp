#include "stdafx.h"

#include "TimeLabel.h"

TimeLabel::TimeLabel()
{
    SetValue(1, 1);
}

void TimeLabel::SetPosition(const FPoint& center)
{
    _text = center;
}

void TimeLabel::Draw()
{
    float scale = 3;

    Render::device.SetTexturing(true);
    {
        Render::BindFont("arial");
        Render::PrintString(_text, "Time:", scale, RightAlign, CenterAlign);
    }

    float totalSize = Render::getFontHeight() * scale;
    float currentSize = totalSize * _time / _total;
    float shift = 20;

    Render::device.SetTexturing(false);
    {
        Render::PushMatrix m;

        float s = currentSize / 2;
        Render::device.MatrixTranslate(_text + FPoint(shift + s, 0));
        Render::DrawRect(IRect(-s, -s, currentSize, currentSize));
    }
}

void TimeLabel::SetValue(uint32_t remain, uint32_t total)
{
    _time = remain;
    _total = total;
}
