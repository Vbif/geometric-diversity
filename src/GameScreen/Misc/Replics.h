#pragma once

#include "SquareLife.h"

/// –еплики, произносимые квадратными аватарами
class Replics {
public:
    Replics();
    void StartReplic(SquareLife* soldier, SquareLife* general);
    void RandomReplic();

private:
    void SaySequence(const std::vector<std::string>& seq);
    void SaySequence1(const std::vector<std::string>& seq);
    void SaySequence2(const std::vector<std::string>& seq);
    void SaySequence3(const std::vector<std::string>& seq);

private:
    SquareLife* _general;
    SquareLife* _soldier;
    std::vector<std::vector<std::string>> _replics;
};
