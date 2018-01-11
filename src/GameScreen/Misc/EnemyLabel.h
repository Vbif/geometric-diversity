#pragma once

/// Строка, отображающая количество уничтоженных врагов
/// в виде двух квадратов.
class EnemyLabel {
public:
    EnemyLabel();
    void SetPosition(const FPoint& center);
    void Draw();
    void SetValue(size_t killed, size_t total);

private:
    FPoint _textPosition;
    size_t _killedCount;
    size_t _totalCount;
    std::string _textCaption;
};
