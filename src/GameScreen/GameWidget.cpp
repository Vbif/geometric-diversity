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
    _options.LoadFrom("input.txt");

    int width = Constants::WindowWidth;
    int height = Constants::WindowHeight;

    int minSide = std::min(width, height);
    _field.Init(FPoint(width / 2, height / 2), minSide);

    // Все позиции рассчитаны на разрешение 1024х768
    FRect soldierBalloon(10, 230, 130, 260);
    _soldier.Init(FPoint(300, 55), soldierBalloon);
    _general.Init(FPoint(724, 55),
        soldierBalloon.MovedBy(FPoint(width - soldierBalloon.RightTop().x, 0)));

    _enemyLabel.SetPosition(FPoint(850, 640));
    _timeLabel.SetPosition(FPoint(850, 700));

    Restart();
}

void GameWidget::Restart()
{
    _gameTimer = Timer(_options.Time);
    _field.Restart(_options.EnemiesCount, _options.Speed);
}

void GameWidget::Draw()
{
    float alpha = 1.0f;
    if (Core::mainScreen.GetTopLayer()->name != "GameLayer")
        alpha = 0.5f;

    Render::PushAlphaMul m(alpha);

    _field.Draw();
    _soldier.Draw();
    _general.Draw();
    _enemyLabel.Draw();
    _timeLabel.Draw();

    IPoint mouse_pos = Core::mainInput.GetMousePos();
    Render::BindFont("arial");
    Render::PrintString(924 + 100 / 2, 35, utils::lexical_cast(mouse_pos.x) + ", " + utils::lexical_cast(mouse_pos.y), 1.f, CenterAlign);
}

void Popup(const char* cause)
{
    Core::mainScreen.pushLayer("RestartGameLayer");
    Core::guiManager.getLayer("RestartGameLayer")->getWidget("RestartGameWidget")->AcceptMessage(Message("PopupCause", cause));
}

void GameWidget::Update(float dt)
{
    // pause
    if (Core::mainScreen.GetTopLayer()->name != "GameLayer")
        return;

    _field.Update(dt);

    size_t enemyTotal = _field.TotalEnemyCount();
    size_t enemyRemain = _field.RemainEnemyCount();
    _enemyLabel.SetValue(enemyTotal - enemyRemain, enemyTotal);

    if (enemyRemain == 0)
        Popup("win");

    _gameTimer.Update(dt);
    if (_gameTimer.IsExpired())
        Popup("fail");

    uint32_t timeTotal = _options.Time;
    uint32_t timeRemain = _gameTimer.Remain();
    _timeLabel.SetValue(timeRemain, timeTotal);
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
    // Виджету могут посылаться сообщения с параметрами.
    //

    const std::string& publisher = message.getPublisher();
    const std::string& data = message.getData();

    if (publisher == "RestartMessage")
        Restart();
}

void GameWidget::KeyPressed(int keyCode)
{
    //
    // keyCode - виртуальный код клавиши.
    // В качестве значений для проверки нужно использовать константы VK_.
    //

    if (keyCode == VK_A) {
        // Реакция на нажатие кнопки A
    }
}

void GameWidget::CharPressed(int unicodeChar)
{
    //
    // unicodeChar - Unicode код введённого символа
    //

    if (unicodeChar == L'а') {
        // Реакция на ввод символа 'а'
    }
}
