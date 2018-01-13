#pragma once

#include "stdafx.h"

#include "Misc\EnemyLabel.h"
#include "Misc\Replics.h"
#include "Misc\SquareGeneral.h"
#include "Misc\SquareSoldier.h"
#include "Misc\TimeLabel.h"
#include "Options.h"
#include "Shooter\Field.h"
#include "Utils\BackgroundEffect.h"
#include "Utils\Timer.h"

///
/// Данный виджет представляет весь игровой экран
///
class GameWidget : public GUI::Widget {
public:
    GameWidget(const std::string& name, rapidxml::xml_node<>* elem);

    void Draw() override;
    void Update(float dt) override;

    void AcceptMessage(const Message& message) override;

    bool MouseDown(const IPoint& mouse_pos) override;
    void MouseMove(const IPoint& mouse_pos) override;
    void MouseUp(const IPoint& mouse_pos) override;

    void KeyPressed(int keyCode) override;
    void CharPressed(int unicodeChar) override;

private:
    void Init();
    void Restart(bool first);

private:
    // настройки уровня
    Options _options;
    // все объекты
    ScreenObjectComposite _objects;

    // объекты, которыми управляем
    SquareSoldier* _soldier;
    SquareGeneral* _general;
    EnemyLabel* _enemyLabel;
    TimeLabel* _timeLabel;
    Field* _field;

    Timer _gameTimer;
    Replics _replics;
    Timer _replicTimer;
};
