#include "stdafx.h"

#include "BlurEffect.h"

static const float radius = 4;

BlurEffect::BlurEffect()
{
    RenderTargetConfig rti;
    rti.multisampleType = MultisampleType::MULTISAMPLE_4_SAMPLES;

    auto size = Core::appInstance->GetMainWindow()->GetClientSizes();
    int width = math::GetNextPow2(size.width);
    int height = math::GetNextPow2(size.height);

    _original = Render::device.CreateRenderTarget(width, height, rti);
    _halfBlurred = Render::device.CreateRenderTarget(width, height);
    _shader = Core::resourceManager.Get<Render::ShaderProgram>("myshader");
}

BlurEffect::~BlurEffect()
{
}

void BlurEffect::Begin()
{
    Render::device.BeginRenderTo(_original);
    Render::device.Clear(Color::BLACK);
}

void BlurEffect::End()
{
    Render::device.EndRenderTo();

    Render::device.SetTexturing(true);

    // горизонтальное размытие
    Render::device.BeginRenderTo(_halfBlurred);
    Render::device.Clear(Color::BLACK);

    _shader->Bind();
    _shader->SetUniform("dir", 1.f, 0.f);
    _shader->SetUniform("resolution", (float)_original->Width());
    _shader->SetUniform("radius", radius);

    _original->Draw(FPoint());

    _shader->Unbind();
    Render::device.EndRenderTo();

    // вертикальное размытие
    _shader->Bind();
    _shader->SetUniform("dir", 0.f, 1.f);
    _shader->SetUniform("resolution", (float)_original->Height());
    _shader->SetUniform("radius", radius);

    _halfBlurred->Draw(FPoint());

    _shader->Unbind();

    // еще раз нарисуем оригинал
    Render::PushBlendMode m(BlendMode::Add);
    _original->Draw(FPoint());
}
