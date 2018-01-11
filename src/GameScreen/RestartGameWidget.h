#pragma once

///
/// Данный виджет представляет popup для перезапуска игры
///
class RestartGameWidget : public GUI::Widget {
public:
    RestartGameWidget(const std::string& name, rapidxml::xml_node<>* elem);

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

private:
    FRect _windowRect;
    FRect _buttonRestart;
    FRect _buttonQuit;
    bool _isWin;
    size_t _killedCount;
    std::string _textWin;
    std::string _textLose;
    std::string _textRestart;
    std::string _textExit;
    std::string _textKilled;
};
