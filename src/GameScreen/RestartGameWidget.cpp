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
    int width = Constants::WindowWidth;
    int height = Constants::WindowHeight;

    _windowRect = IRect(100, 100, width - 200, height - 200);
    _buttonRestart = IRect(100, 100, 200, 40);
    _buttonQuit = IRect(_buttonRestart.RightTop().x, 100, 200, 40);

    isWin = false;
}

void RestartGameWidget::Draw()
{
    Render::device.SetTexturing(false);

    Render::DrawFrame(_windowRect);
    Render::DrawFrame(_buttonRestart);
    Render::DrawFrame(_buttonQuit);

    Render::device.SetTexturing(true);
    Render::BindFont("arial");

    Render::PrintString(FRect(_windowRect).CenterPoint(), isWin ? "You win" : "You failed", 5, CenterAlign, CenterAlign);
    Render::PrintString(FRect(_buttonRestart).CenterPoint(), "Restart", 3, CenterAlign, CenterAlign);
    Render::PrintString(FRect(_buttonQuit).CenterPoint(), "Quit", 3, CenterAlign, CenterAlign);
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
    if (_buttonRestart.Contains(mouse_pos)) {
        Core::mainScreen.popLayer();
        Core::guiManager.getLayer("GameLayer")->getWidget("GameWidget")->AcceptMessage(Message("RestartMessage", ""));
    }
    if (_buttonQuit.Contains(mouse_pos)) {
        Core::appInstance->CloseWindow();
    }
}

void RestartGameWidget::AcceptMessage(const Message& message)
{
    //
    // Виджету могут посылаться сообщения с параметрами.
    //

    const std::string& publisher = message.getPublisher();
    const std::string& data = message.getData();

    if (publisher == "PopupCause") {
        isWin = data == "win";
    }
}

void RestartGameWidget::KeyPressed(int keyCode)
{
    //
    // keyCode - виртуальный код клавиши.
    // В качестве значений для проверки нужно использовать константы VK_.
    //

    if (keyCode == VK_A) {
        // Реакция на нажатие кнопки A
    }
}

void RestartGameWidget::CharPressed(int unicodeChar)
{
    //
    // unicodeChar - Unicode код введённого символа
    //

    if (unicodeChar == L'а') {
        // Реакция на ввод символа 'а'
    }
}
