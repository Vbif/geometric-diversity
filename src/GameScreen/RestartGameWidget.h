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
    IRect _windowRect;
    IRect _buttonRestart;
    IRect _buttonQuit;
    bool isWin;
};
