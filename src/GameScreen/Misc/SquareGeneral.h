#pragma once

#include "SquareLife.h"

///  вадратный генерал
class SquareGeneral : public SquareLife {
public:
    SquareGeneral(const FPoint& position, const FRect& balloon);
};
