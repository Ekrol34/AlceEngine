#include "Ground.hpp"

using namespace alce;

SampleScene::Ground::Ground()
{
	
}

//Custom methods implementation
#pragma region implementation


#pragma endregion

//Inherited methods
#pragma region inherited

void SampleScene::Ground::Init()
{
    AddTag("Ground");
    
    rigidbody2d = std::make_shared<Rigidbody2D>();
    AddComponent(rigidbody2d);

    rigidbody2d->CreateBody(
        std::make_shared<RectShape>(Vector2(1150.0f, 50.0f)),
        BodyType::kinematic_body,
        true
    );

    tilemap = std::make_shared<TileMap>();
    AddComponent(tilemap);

    tilemap->Load("dudegame/grounds/ground1/ground1_tmap.json", "dudegame/grounds/ground1/ground1_tset.png", 10);
    tilemap->scale = Vector2(0.005f, 0.005f);
    tilemap->offset = Vector2(0.0f, -5.5f);
}

void SampleScene::Ground::Start()
{

}

void SampleScene::Ground::Update()
{
	
}

void SampleScene::Ground::SetterManager(String name, String value)
{
    if(name == "position")
    {
        Vector2 position = Vector2(value.Split(",")[0].ParseFloat(), value.Split(",")[1].ParseFloat());
        rigidbody2d->SetPosition(position, true);
    }

    if(name == "tilemap_scale")
    {
        Vector2 scale = Vector2(value.Split(",")[0].ParseFloat(), value.Split(",")[1].ParseFloat());
        tilemap->scale = scale;
    }

    if(name == "tilemap_offset")
    {
        Vector2 offset = Vector2(value.Split(",")[0].ParseFloat(), value.Split(",")[1].ParseFloat());
        tilemap->offset = offset;
    }

    if(name == "scale")
    {
        Vector2 scale = Vector2(value.Split(",")[0].ParseFloat(), value.Split(",")[1].ParseFloat());
        transform.scale = scale;
    }

    if(name == "text")
    {
        textRenderer->SetNewText(value);
    }
}

#pragma endregion