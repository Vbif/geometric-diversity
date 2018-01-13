#include "stdafx.h"

#include "SquareSoldier.h"

SquareSoldier::SquareSoldier(const FPoint& position, const FRect& balloon)
    : SquareLife(position, 60, balloon)
{
}
