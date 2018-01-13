#pragma once

#include "Framework\ScreenObject.h"
#include "Utils\Timer.h"

/// ¬сплывающее сообщение дл€ квадратных аватаров
class Balloon : public ScreenObject {
public:
    Balloon(const FRect& mainPosition, const FPoint& firstPoint);
    void Draw() override;
    void Update(float dt) override;
    void Show(const std::string& text);
    bool IsInactive();
    void Hide();

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
