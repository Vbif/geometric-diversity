#include "stdafx.h"

#include "Constants.h"
#include "RestartGameWidget.h"

RestartGameWidget::RestartGameWidget(const std::string& name, rapidxml::xml_node<>* elem)
    : Widget(name)
{
    _textWin = codepage_to_utf8("Победа!", 1251);
    _textLose = codepage_to_utf8("Вы проиграли!", 1251);
    _textRestart = codepage_to_utf8("Заново", 1251);
    _textExit = codepage_to_utf8("Выйти", 1251);

    Init();
}

void RestartGameWidget::Init()
{
    int width = Constants::WindowWidth;
    int height = Constants::WindowHeight;

    _windowRect = FRect(IRect(100, 100, width - 200, height - 200));
    _buttonRestart = FRect(IRect(100, 100, 200, 40));
    _buttonQuit = FRect(IRect(_buttonRestart.RightTop().x, 100, 200, 40));

    isWin = false;
}

void RestartGameWidget::Draw()
{
    Render::PushTexturing t0(false);

    Render::DrawWireframeRect(_windowRect, 4);
    Render::DrawWireframeRect(_buttonRestart, 4);
    Render::DrawWireframeRect(_buttonQuit, 4);

    Render::PushTexturing t1(true);
    Render::BindFont("arial");

    Render::PrintString(_windowRect.CenterPoint(), isWin ? _textWin : _textLose, 5, CenterAlign, CenterAlign);
    Render::PrintString(_buttonRestart.CenterPoint(), _textRestart, 3, CenterAlign, CenterAlign);
    Render::PrintString(_buttonQuit.CenterPoint(), _textExit, 3, CenterAlign, CenterAlign);
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

        MM::manager.FadeAll(0.5);
        MM::manager.FadeInTrack(isWin ? "win" : "lose", 0.1);
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
