#pragma once

#include <array>

#include "Balloon.h"

/// Общая реализация для квадратных аватаров
class SquareLife {
public:
    SquareLife();
    void Draw();
    void Update();

protected:
    void Init(const FPoint& position, float size, const FRect& balloonPosition);

private:
    FPoint _center;
    float _size;

    FRect _frame;
    std::array<FRect, 2> _eyes;

    std::unique_ptr<Balloon> _balloon;
};
