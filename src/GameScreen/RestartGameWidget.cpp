#include "stdafx.h"

#include "Constants.h"
#include "RestartGameWidget.h"

RestartGameWidget::RestartGameWidget(const std::string& name, rapidxml::xml_node<>* elem)
    : Widget(name)
{
    Init();
}

void RestartGameWidget::Init()
{
}

void RestartGameWidget::Draw()
{
    int width = Constants::WindowWidth;
    int height = Constants::WindowHeight;

    Render::device.SetTexturing(true);
    Render::BindFont("arial");
    Render::PrintString(FPoint(width / 2, height / 2), "You win", 5, CenterAlign, CenterAlign);
}

void RestartGameWidget::Update(float dt)
{
}

bool RestartGameWidget::MouseDown(const IPoint& mouse_pos)
{
    return false;
}

void RestartGameWidget::MouseMove(const IPoint& mouse_pos)
{
}

void RestartGameWidget::MouseUp(const IPoint& mouse_pos)
{
}

void RestartGameWidget::AcceptMessage(const Message& message)
{
    //
    // ������� ����� ���������� ��������� � �����������.
    //

    const std::string& publisher = message.getPublisher();
    const std::string& data = message.getData();
}

void RestartGameWidget::KeyPressed(int keyCode)
{
    //
    // keyCode - ����������� ��� �������.
    // � �������� �������� ��� �������� ����� ������������ ��������� VK_.
    //

    if (keyCode == VK_A) {
        // ������� �� ������� ������ A
    }
}

void RestartGameWidget::CharPressed(int unicodeChar)
{
    //
    // unicodeChar - Unicode ��� ��������� �������
    //

    if (unicodeChar == L'�') {
        // ������� �� ���� ������� '�'
    }
}
