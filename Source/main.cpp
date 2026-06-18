#include "Project/Scenes/Scenes.hpp"

using namespace alce;

int main()
{
    Alce.Window("AlceEngine Sample", DisplayMode::Default);
    // Alce.SetWindowIcon("dudegame/dudegame_icon.png");
    Alce.stanby = true;

    Debug.SetWaitTime(0);

    Alce.AddScene<IntroScene::Intro>();
    Alce.AddScene<SharedScene::Shared>();
    Alce.AddScene<SampleScene::Sample>();
    Alce.AddScene<Test1Scene::Test1>();

    Alce.SetCurrentScene("Intro");
    
    Alce.Run();

    return 0;
}
