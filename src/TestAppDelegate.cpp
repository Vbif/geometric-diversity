#include "stdafx.h"

#include "Constants.h"
#include "GameScreen\GameWidget.h"
#include "GameScreen\RestartGameWidget.h"
#include "TestAppDelegate.h"

TestAppDelegate::TestAppDelegate()
{
}

void TestAppDelegate::GameContentSize(int deviceWidth, int deviceHeight, int& width, int& height)
{
    //
    // Здесь задаётся размер игрового экрана в логических единицах.
    //
    // Это значит, что и в оконном, и в полноэкранном режиме размер экрана
    // всегда будет равен WINDOW_WIDTH x WINDOW_HEIGHT "пикселей".
    //
    width = Constants::WindowWidth;
    height = Constants::WindowHeight;
}

void TestAppDelegate::ScreenMode(DeviceMode& mode)
{
    mode = DeviceMode::Windowed;
}

void TestAppDelegate::RegisterTypes()
{
    //
    // Чтобы можно было декларативно использовать виджет в xml по имени,
    // его необходимо зарегистрировать таким образом.
    //
    REGISTER_WIDGET_XML(GameWidget, "GameWidget");
    REGISTER_WIDGET_XML(RestartGameWidget, "RestartGameWidget");
}

void TestAppDelegate::LoadResources()
{
    //
    // Обычно в этом методе выполняется скрипт, в котором определяется,
    // какие ресурсы нужно загрузить и какой игровой слой положить на экран.
    //
    Core::LuaExecuteStartupScript("start.lua");
}

void TestAppDelegate::OnResourceLoaded()
{
    if (Core::appInstance->AllResourcesLoaded()) {
        Core::appInstance->SetLoaded();
    }
}

void TestAppDelegate::OnPreDraw()
{
    if (!_effect)
        _effect.reset(new BlurEffect());
    _effect->Begin();
}

void TestAppDelegate::OnPostDraw()
{
    _effect->End();

    if (!Render::isFontLoaded("arial"))
        return;

    //
    // Перед вызовом метода Render::PrintString() нужно привязать нужный шрифт
    //
    Render::BindFont("arial");

    int dy = Render::getFontHeight();
    int x = 0; // Render::device.Width() - 5;
    int y = Render::device.Height() - 20;

    Render::PrintString(x, y, std::string("FPS: ") + utils::lexical_cast(Core::appInstance->GetCurrentFps()), 1.0f, LeftAlign, BottomAlign);
    /*Render::PrintString(x, y -= dy, std::string("Video: ") + utils::lexical_cast(Render::device.GetVideoMemUsage() / 1024) + std::string("K"), 1.0f, RightAlign, BottomAlign);
    Render::PrintString(x, y -= dy, std::string("Audio: ") + utils::lexical_cast(Core::resourceManager.GetMemoryInUse<MM::AudioResource>() / 1024) + std::string("K"), 1.0f, RightAlign, BottomAlign);
    Render::PrintString(x, y -= dy, std::string("Animations: ") + utils::lexical_cast((Core::resourceManager.GetMemoryInUse<Render::StreamingAnimation>() + Core::resourceManager.GetMemoryInUse<Render::Animation>()) / 1024) + std::string("K"), 1.0f, RightAlign, BottomAlign);
    Render::PrintString(x, y -= dy, std::string("Textures: ") + utils::lexical_cast(Core::resourceManager.GetMemoryInUse<Render::Texture>() / 1024) + std::string("K"), 1.0f, RightAlign, BottomAlign);
    Render::PrintString(x, y -= dy, std::string("Particles: ") + utils::lexical_cast(Core::resourceManager.GetMemoryInUse<ParticleEffect>() / 1024) + std::string("K"), 1.0f, RightAlign, BottomAlign);
    Render::PrintString(x, y -= dy, std::string("Models: ") + utils::lexical_cast(Core::resourceManager.GetMemoryInUse<Render::ModelAnimation>() / 1024) + std::string("K"), 1.0f, RightAlign, BottomAlign);*/
}
