#pragma once

#include "SquareLife.h"

/// ���������� ������ (�����)
class SquareSoldier : public SquareLife {
public:
    SquareSoldier(const FPoint& position, const FRect& balloon);
};
