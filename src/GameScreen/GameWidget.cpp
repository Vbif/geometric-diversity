#include "stdafx.h"

#include "Constants.h"
#include "GameWidget.h"

GameWidget::GameWidget(const std::string& name, rapidxml::xml_node<>* elem)
    : Widget(name)
{
    Init();
}

void GameWidget::Init()
{
    int width = Constants::WindowWidth;
    int height = Constants::WindowHeight;
    Core::appDelegate->GameContentSize(0, 0, width, height);

    int minSide = std::min(width, height);
    _field.Init(FPoint(width / 2, height / 2), minSide);

    // ��� ������� ���������� �� ���������� 1024�768
    FRect soldierBalloon(10, 230, 130, 260);
    _soldier.Init(FPoint(300, 55), soldierBalloon);
    _general.Init(FPoint(724, 55), soldierBalloon.MovedBy(FPoint(width - soldierBalloon.RightTop().x, 0)));
}

void GameWidget::Draw()
{
    _field.Draw();
    _soldier.Draw();
    _general.Draw();

    IPoint mouse_pos = Core::mainInput.GetMousePos();
    Render::BindFont("arial");
    Render::PrintString(924 + 100 / 2, 35, utils::lexical_cast(mouse_pos.x) + ", " + utils::lexical_cast(mouse_pos.y), 1.f, CenterAlign);
}

void GameWidget::Update(float dt)
{
    _field.Update(dt);
}

bool GameWidget::MouseDown(const IPoint& mouse_pos)
{

    return false;
}

void GameWidget::MouseMove(const IPoint& mouse_pos)
{
}

void GameWidget::MouseUp(const IPoint& mouse_pos)
{
}

void GameWidget::AcceptMessage(const Message& message)
{
    //
    // ������� ����� ���������� ��������� � �����������.
    //

    const std::string& publisher = message.getPublisher();
    const std::string& data = message.getData();
}

void GameWidget::KeyPressed(int keyCode)
{
    //
    // keyCode - ����������� ��� �������.
    // � �������� �������� ��� �������� ����� ������������ ��������� VK_.
    //

    if (keyCode == VK_A) {
        // ������� �� ������� ������ A
    }
}

void GameWidget::CharPressed(int unicodeChar)
{
    //
    // unicodeChar - Unicode ��� ��������� �������
    //

    if (unicodeChar == L'�') {
        // ������� �� ���� ������� '�'
    }
}
