#include "Shared.hpp"
#include "Player/Player.hpp"

using namespace alce;

SharedScene::Shared::Shared() : Scene("Shared")
{
	DevelopmentMode(true);
	InitPhysics(Vector2(0.0f, -9.8f));
}

//Custom methods implementation
#pragma region implementation


#pragma endregion

//Inherited methods
#pragma region inherited

void SharedScene::Shared::Init()
{
	Factory.RegisterCreator("SharedScene::Player", []() {
		return std::make_shared<SharedScene::Player>();
	});

	
}

void SharedScene::Shared::Start()
{
	
}

#pragma endregion