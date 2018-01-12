#pragma once

#include <array>
#include <functional>

#include "Balloon.h"

/// Общая реализация для квадратных аватаров
class SquareLife {
public:
    using SayCallback = std::function<void(void)>;

public:
    SquareLife();
    void Draw();
    void Update(float dt);
    void Say(const std::string& text, const SayCallback& callback = nullptr);
    void Shut();

protected:
    void Init(const FPoint& position, float size, const FRect& balloonPosition);

private:
    FPoint _center;
    float _size;

    FRect _frame;
    std::array<FRect, 2> _eyes;

    std::unique_ptr<Balloon> _balloon;

    SayCallback _callback;
};
