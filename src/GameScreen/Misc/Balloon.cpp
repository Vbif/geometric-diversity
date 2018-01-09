#include "stdafx.h"

#include "Balloon.h"

static const float timePopup = 0.3;
static const float timeShow = 2;
static const float timePopdown = 0.3;

Balloon::Balloon(const FRect& mainPosition, const FPoint& firstPoint)
    : _mainBallon(mainPosition)
    , _state(State::Hidden)
{
    auto mainLeft = _mainBallon.LeftBottom();
    auto mainRight = _mainBallon.RightBottom();

    auto mainClosest = firstPoint.GetDistanceTo(mainLeft) < firstPoint.GetDistanceTo(mainRight)
        ? mainLeft
        : mainRight;

    float sizes[3] = { 10, 20, 30 };
    float xdelta = (mainClosest - firstPoint).x / _targetBallons.size();

    for (size_t i = 0; i < _targetBallons.size(); i++) {

        float x = firstPoint.x + xdelta * i;
        float y = firstPoint.y - math::log2(0.1f + 0.33f * i);
        _targetBallons[i] = FRect(x, x + sizes[i], y, y + sizes[i]);
    }
}

void Balloon::Draw()
{
    size_t targetBallonCount = 0;
    size_t maxCount = _targetBallons.size();

    switch (_state) {
    case State::Popup:
        targetBallonCount = _timer.Elapsed() * maxCount / _timer.Total();
        break;
    case State::Show:
        targetBallonCount = maxCount;
        break;
    case State::Popdown:
        targetBallonCount = _timer.Remain() * maxCount / _timer.Total();
        break;
    }

    Render::device.SetTexturing(false);

    for (size_t i = 0; i < targetBallonCount; i++)
        Render::DrawRectWireframe(_targetBallons[i]);

    if (_state == State::Show) {
        Render::DrawRectWireframe(_mainBallon);

        Render::device.SetTexturing(true);
        Render::BindFont("arial");
        Render::PrintString(_mainBallon.CenterPoint(), _text, 1, CenterAlign, CenterAlign);
    }
}

void Balloon::Update(float dt)
{
    if (_state == State::Hidden)
        return;

    _timer.Update(dt);
    if (!_timer.IsExpired())
        return;

    switch (_state) {
    case State::Popup:
        _state = State::Show;
        _timer = Timer(timeShow);
        break;
    case State::Show:
        _state = State::Popdown;
        _timer = Timer(timePopdown);
        break;
    case State::Popdown:
        _state = State::Hidden;
        break;
    default:
        Log::Warn("Illegal Show() on Balloon");
        break;
    }
}

void Balloon::Show(const std::string& text)
{
    if (_state != State::Hidden) {
        Log::Error("Illegal Show() on Balloon");
        return;
    }

    _text = text;
    _state = State::Popup;
    _timer = Timer(timePopup);
}

bool Balloon::IsInactive()
{
    return _state == State::Hidden;
}
