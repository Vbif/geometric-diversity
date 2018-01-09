#pragma once

#include "SquareLife.h"

class Replics {
public:
    Replics();
    void StartReplic(SquareLife& soldier, SquareLife& general);

private:
    void SaySequence3(const std::vector<std::string>& seq);

private:
    SquareLife* _general;
    SquareLife* _soldier;
    std::vector<std::vector<std::string>> _replics;
};
