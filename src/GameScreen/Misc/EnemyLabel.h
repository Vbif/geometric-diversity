#pragma once

class EnemyLabel {
public:
    EnemyLabel();
    void SetPosition(const FPoint& center);
    void Draw();
    void SetValue(size_t killed, size_t total);

private:
    FPoint _text;
    size_t _killedCount;
    size_t _totalCount;
};
