#include "Intro.hpp"
#include "Renderer/Renderer.hpp"

using namespace alce;

IntroScene::Intro::Intro() : Scene("Intro")
{
	DevelopmentMode(false);
	InitPhysics(Vector2(0.0f, 0.0f));
}

//Custom methods implementation
#pragma region implementation


#pragma endregion

//Inherited methods
#pragma region inherited

void IntroScene::Intro::Init()
{
	RendererPtr renderer = std::make_shared<Renderer>();
	AddGameObject(renderer, "Renderer");
}

void IntroScene::Intro::Start()
{
	
}

#pragma endregion