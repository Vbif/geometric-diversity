#pragma once

#include <memory>
#include <vector>

class ScreenObject {
public:
    virtual void Draw();
    virtual void Update(float dt);
    virtual ~ScreenObject();
};

class ScreenObjectComposite : public ScreenObject {
public:
    void Draw() override;
    void Update(float dt) override;

    void AddChild(ScreenObject* child);

private:
    std::vector<std::unique_ptr<ScreenObject>> _children;
};
