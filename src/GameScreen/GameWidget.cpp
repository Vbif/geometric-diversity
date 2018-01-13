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

    // Все позиции рассчитаны на разрешение 1024х768
    int width = Constants::WindowWidth;
    int height = Constants::WindowHeight;

    // фон
    auto background = new BackgroundEffect();
    _objects.AddChild(background);

    // игровой мир
    auto gameWorld = new GameWorld();
    gameWorld->SetAdDefault();
    _objects.AddChild(gameWorld);

    // отображения кол-ва врагов
    _enemyLabel = new EnemyLabel();
    _enemyLabel->SetPosition(FPoint(850, 640));
    _objects.AddChild(_enemyLabel);

    // отображения кол-ва времени уровня
    _timeLabel = new TimeLabel();
    _timeLabel->SetPosition(FPoint(850, 700));
    _objects.AddChild(_timeLabel);

    // квадратные аватары
    FRect soldierBalloon(10, 230, 130, 260);
    FRect generalBallon = soldierBalloon.MovedBy(FPoint(width - soldierBalloon.RightTop().x - 10, 0));
    _soldier = new SquareSoldier(FPoint(300, 35), soldierBalloon);
    _general = new SquareGeneral(FPoint(724, 55), generalBallon);
    _objects.AddChild(_soldier);
    _objects.AddChild(_general);

    int minSide = std::min(width, height);
    _field.Init(FPoint(width / 2, height / 2), minSide);

    Restart(true);
}

void GameWidget::Restart(bool first)
{
    _gameTimer = Timer(_options.Time);
    _field.Restart(_options.EnemiesCount, _options.Speed);

    if (first)
        _replics.StartReplic(_soldier, _general);
    else
        _replics.RandomReplic();
    // скажем еще случайных фраз, если время на прохождение уровня большое
    _replicTimer = Timer(21);

    MM::manager.StopAll();
    MM::manager.PlayTrack("background", true, 0.5);
}

void GameWidget::Draw()
{
    float alpha = 1.0f;
    if (Core::mainScreen.GetTopLayer()->name != "GameLayer")
        alpha = 0.3f;

    Render::PushAlphaMul m(alpha);

    _objects.Draw();

    _field.Draw();

    IPoint mouse_pos = Core::mainInput.GetMousePos();
    Render::BindFont("arial");
    Render::PrintString(924 + 100 / 2, 35, utils::lexical_cast(mouse_pos.x) + ", " + utils::lexical_cast(mouse_pos.y), 1.f, CenterAlign);
}

void Popup(const char* cause, size_t killedCount)
{
    Core::mainScreen.pushLayer("RestartGameLayer");
    Core::guiManager.getLayer("RestartGameLayer")->getWidget("RestartGameWidget")->AcceptMessage(Message("PopupCause", cause, killedCount));
}

void GameWidget::Update(float dt)
{
    // pause
    if (Core::mainScreen.GetTopLayer()->name != "GameLayer")
        return;

    _objects.Update(dt);

    _field.Update(dt);

    size_t enemyTotal = _field.TotalEnemyCount();
    size_t enemyRemain = _field.RemainEnemyCount();
    size_t enemyKilled = enemyTotal - enemyRemain;
    _enemyLabel->SetValue(enemyKilled, enemyTotal);

    if (enemyRemain == 0)
        Popup("win", enemyKilled);

    _gameTimer.Update(dt);
    if (_gameTimer.IsExpired())
        Popup("fail", enemyKilled);

    uint32_t timeTotal = _options.Time;
    uint32_t timeRemain = _gameTimer.Remain();
    _timeLabel->SetValue(timeRemain, timeTotal);

    _replicTimer.Update(dt);
    if (_replicTimer.IsExpired()) {
        _replicTimer.Reset();
        _replics.RandomReplic();
    }
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
        Restart(false);
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
