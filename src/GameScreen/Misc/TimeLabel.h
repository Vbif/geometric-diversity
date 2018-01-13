#pragma once

#include "Framework\ScreenObject.h"

/// ������, ������������ ���������� ������� � ���� �������������� ��������
class TimeLabel : public ScreenObject {
public:
    TimeLabel();
    void SetPosition(const FPoint& center);
    void Draw() override;
    void SetValue(uint32_t remain, uint32_t total);

private:
    FPoint _textPosition;
    uint32_t _time;
    uint32_t _total;
    std::string _textCaption;
};
