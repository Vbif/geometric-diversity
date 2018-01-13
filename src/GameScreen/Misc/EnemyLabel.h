#pragma once

#include "Framework\ScreenObject.h"

/// Строка, отображающая количество уничтоженных врагов
/// в виде двух квадратов.
class EnemyLabel : public ScreenObject {
public:
    EnemyLabel();
    void SetPosition(const FPoint& center);
    void Draw() override;
    void SetValue(size_t killed, size_t total);

private:
    FPoint _textPosition;
    size_t _killedCount;
    size_t _totalCount;
    std::string _textCaption;
};
