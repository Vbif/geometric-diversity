#pragma once

class Timer {
private:
    float _waitTime;
    float _currentTime;

public:
    Timer(float time)
        : _waitTime(time)
        , _currentTime(0)
    {
    }

    Timer()
        : Timer(0)
    {
    }

    void Update(float dt)
    {
        _currentTime += dt;
        if (_currentTime > _waitTime)
            _currentTime = _waitTime;
    }

    bool IsExpired() const
    {
        return _currentTime >= _waitTime;
    }

    void Reset()
    {
        _currentTime = 0;
    }

    float Elapsed() const
    {
        return _currentTime;
    }

    float Remain() const
    {
        return _waitTime - _currentTime;
    }
};
