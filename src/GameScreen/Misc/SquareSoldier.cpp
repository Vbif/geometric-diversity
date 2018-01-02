#include "stdafx.h"

#include "SquareSoldier.h"

void SquareSoldier::Init(const FPoint& position, const FRect& balloon)
{
    SquareLife::Init(position, 100, balloon);
}
