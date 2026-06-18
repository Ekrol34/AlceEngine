#include "Tree.hpp"

using namespace alce;

SampleScene::Tree::Tree(Vector2 position)
{
	transform.position = position;
}

//Custom methods implementation
#pragma region implementation


#pragma endregion

//Inherited methods
#pragma region inherited

void SampleScene::Tree::Init()
{   
    this->sortingLayer = 2;
	spriteRenderer = std::make_shared<SpriteRenderer>();
    AddComponent(spriteRenderer);

    // lightMesh = std::make_shared<LightMesh2D>(std::make_shared<CircleShape>(30));
    // lightMesh->SetOffset(0, 2);
    // AddComponent(lightMesh);

    lightingArea = std::make_shared<alce::LightingArea2D>();
    lightingArea->SetSize(200, 200);
    lightingArea->SetOffset(-3.5f, 3.5f);
    AddComponent(lightingArea);
    
    spriteRenderer->AddTexture("tree/sprite.png", "sprite");
    spriteRenderer->SetTexture("sprite");
}

void SampleScene::Tree::Start()
{

}

void SampleScene::Tree::Update()
{

}

void SampleScene::Tree::SetterManager(String name, String value)
{
    if(name == "position")
    {
        transform.position.x = value.Split(",")[0].ParseFloat();
        transform.position.y = value.Split(",")[1].ParseFloat();
        Debug.Log(transform.position.ToString());
    }

    if(name == "offset")
    {
        lightMesh->SetOffset(value.Split(",")[0].ParseFloat(), value.Split(",")[1].ParseFloat());
    }

    if(name == "size")
    {
        lightingArea->SetSize(value.Split(",")[0].ParseFloat(), value.Split(",")[1].ParseFloat());
    }
}

String SampleScene::Tree::GetterManager(String name)
{
    if(name == "position") return transform.position.ToString();

    return "";
}

#pragma endregion