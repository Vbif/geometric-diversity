#pragma once

class EnemyLabel {
public:
    EnemyLabel();
    void SetPosition(const FPoint& textBegin, const FPoint& valueBegin);
    void Draw();
    void SetValue(size_t killed, size_t total);

private:
    FPoint _text;
    FPoint _value;
    size_t _killedCount;
    size_t _totalCount;
};
