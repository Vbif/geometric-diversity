#include "stdafx.h"

#include "BackgroundEffect.h"

BackgroundEffect::BackgroundEffect()
    : _time(0)
{
    _shader = Core::resourceManager.Get<Render::ShaderProgram>("background");
}

BackgroundEffect::~BackgroundEffect()
{
}

void BackgroundEffect::Draw()
{
    Render::PushTexturing t(true);

    auto screen = Core::appInstance->GetMainWindow()->GetClientSizes();

    _shader->Bind();
    _shader->SetUniform("resolution", (float)screen.width, (float)screen.height);
    _shader->SetUniform("time", _time);

    Render::DrawRect(screen);

    _shader->Unbind();
}

void BackgroundEffect::Update(float dt)
{
    _time += dt;
}
