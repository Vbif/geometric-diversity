#pragma once

#include "Utils\Timer.h"

/// ¬сплывающее сообщение дл€ квадратных аватаров
class Balloon {
public:
    Balloon(const FRect& mainPosition, const FPoint& firstPoint);
    void Draw();
    void Update(float dt);
    void Show(const std::string& text);

private:
    enum class State {
        Hidden,
        Popup,
        Show,
        Popdown
    };

private:
    FRect _mainBallon;
    std::array<FRect, 3> _targetBallons;
    std::string _text;
    State _state;
    Timer _timer;
};
