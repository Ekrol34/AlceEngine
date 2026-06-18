#include "LightingArea2D.hpp"

using namespace alce;

LightingArea2D::LightingArea2D() : Component("LightingArea2D")
{
    // lightingArea = std::make_shared<candle::LightingArea>(candle::LightingArea::FOG, Vector2(0, 0).ToPixels().ToVector2f(), size.ToVector2f());
}

//Custom methods implementation
#pragma region implementation

bool LightingArea2D::SetOpacity(float opacity)
{
    if(opacity > 1.0f || opacity < 0)
    {
        Debug.Warning("LightingArea2D::SetOpacity -> LightingArea2D opacity should be between 0.0f and 1.0f");
        return false;
    }
    
    this->opacity = opacity;

    return true;
}

float LightingArea2D::GetOpacity()
{
    return opacity;
}

void LightingArea2D::SetSize(Vector2 size)
{
    compute = true;
    this->size = size;
}

void LightingArea2D::SetSize(float width, float height)
{
    compute = true;
    size = Vector2(width, height);
}

void LightingArea2D::SetOffset(Vector2 offset)
{
    this->offset = offset;
}

void LightingArea2D::SetOffset(float x, float y)
{
    offset = Vector2(x, y);
}

Vector2 LightingArea2D::GetOffset()
{
    return offset;
}

#pragma endregion

//Inherited methods
#pragma region inherited

void LightingArea2D::Init()
{
	
}

void LightingArea2D::Start()
{
	
}

void LightingArea2D::Render()
{
	if(!enabled) return;
    
	lightingArea->clear();

	for(auto& light : lights)
	{
		lightingArea->draw(*light);
	}

	lightingArea->display();

	Alce.GetWindow().draw(*lightingArea.get());
}

void LightingArea2D::DebugRender()
{
	if(!enabled) return;

    Vector2 pos = transform->position + offset;
    pos = pos.ToPixels();

    Vector2 a = pos;
    Vector2 b = pos + Vector2(size.x, 0);
    Vector2 c = pos + Vector2(size.x, size.y);
    Vector2 d = pos + Vector2(0, size.y);

    DrawDottedLine(Alce.GetWindow(), a.ToVector2f(), b.ToVector2f(), sf::Color::White);
    DrawDottedLine(Alce.GetWindow(), b.ToVector2f(), c.ToVector2f(), sf::Color::White);
    DrawDottedLine(Alce.GetWindow(), c.ToVector2f(), d.ToVector2f(), sf::Color::White);
    DrawDottedLine(Alce.GetWindow(), d.ToVector2f(), a.ToVector2f(), sf::Color::White);
}

void LightingArea2D::Update()
{
    Vector2 position = transform->position + offset;
    
    if(compute || lightingArea == nullptr)
    {
        compute = false;
        lightingArea = std::make_shared<candle::LightingArea>(candle::LightingArea::FOG, position.ToPixels().ToVector2f(), size.ToVector2f());
    }

    lightingArea->setPosition(position.ToPixels().ToVector2f());
    lightingArea->setAreaOpacity(opacity);
	lightingArea->setAreaColor(color.ToSFMLColor());

    lights.RemoveIf([](std::shared_ptr<candle::LightSource> light) {
        return light->destroy;
    });
}

#pragma endregion