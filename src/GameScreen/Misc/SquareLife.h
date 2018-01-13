#pragma once

#include <array>
#include <functional>

#include "Balloon.h"

/// Общая реализация для квадратных аватаров
class SquareLife : public ScreenObjectComposite {
public:
    using SayCallback = std::function<void(void)>;

public:
    SquareLife(const FPoint& position, float size, const FRect& balloonPosition);
    void Draw() override;
    void Update(float dt) override;
    void Say(const std::string& text, const SayCallback& callback = nullptr);
    void Shut();

private:
    FPoint _center;
    float _size;

    FRect _frame;
    std::array<FRect, 2> _eyes;

    Balloon* _balloon;

    SayCallback _callback;
};
