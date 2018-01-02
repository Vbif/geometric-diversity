#pragma once

/// ����������� ��������� ��� ���������� ��������
class Balloon {
public:
    Balloon(const FRect& mainPosition, const FPoint& firstPoint);
    void Draw();
    void Update();

private:
    FRect _mainBallon;
    std::array<FRect, 3> _targetBallons;
};
