#pragma once

class TimeLabel {
public:
    TimeLabel();
    void SetPosition(const FPoint& center);
    void Draw();
    void SetValue(uint32_t remain, uint32_t total);

private:
    FPoint _textPosition;
    uint32_t _time;
    uint32_t _total;
    std::string _textCaption;
};
