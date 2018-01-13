#pragma once

#include "SquareLife.h"

///  вадратный солдат (кадет)
class SquareSoldier : public SquareLife {
public:
    SquareSoldier(const FPoint& position, const FRect& balloon);
};
