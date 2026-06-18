#include "SpriteRenderer.hpp"

using namespace alce;

SpriteRenderer::SpriteRenderer() : Component("SpriteRenderer")
{
    sprite = std::make_unique<sf::Sprite>();

    cardinals.Set("top-left", std::make_shared<Vector2>());
    cardinals.Set("top-right", std::make_shared<Vector2>());
    cardinals.Set("bottom-left", std::make_shared<Vector2>());
    cardinals.Set("bottom-right", std::make_shared<Vector2>());
}

#pragma region implementation

bool SpriteRenderer::AddTexture(String file, String name)
{
    if(textures.HasKey(name))
    {
        Debug.Warning("SpriteRenderer::AddTexture -> SpriteRenderer already contains a texture named \"{}\"", {file});
        return false;
    }
    
    auto texture = Alce.GetTexture(file);

    if(texture != nullptr)
    {
        textures.Set(name, texture);
        return true;
    }
    else return false;
}

bool SpriteRenderer::SetTexture(String name)
{
    if(!textures.HasKey(name))
    {
        Debug.Warning("SpriteRenderer::SetTexture -> SpriteRenderer does not contain a texture named \"{}\"", {name});
        return false;
    }

    sprite->setTexture(*textures.Get(name).get(), true);

    return true;
}

bool SpriteRenderer::SetAlpha(int alpha)
{
    if(alpha < 0 || alpha > 255)
    {
        Debug.Warning("SpriteRenderer::SetAlpha -> Alpha value must be between 0 and 255, received: {}", {alpha});
        return false;
    }

    this->alpha = alpha;

    return true;
}

int SpriteRenderer::GetAlpha()
{
    return alpha;
}

bool SpriteRenderer::RemoveTexture(String name)
{
    if(!textures.GetKeyList().Contains(name))
    {
        Debug.Warning("SpriteRenderer::RemoveTexture -> SpriteRenderer does not contain a texture named \"{}\"", {name});
        return false;
    }

    textures.RemoveByKey(name);

    return true;
}

bool SpriteRenderer::SetTextureSmooth(String name, bool flag)
{
    if(!textures.GetKeyList().Contains(name))
    {
        Debug.Warning("SpriteRenderer::SetTextureSmooth -> SpriteRenderer does not contain a texture named \"{name}\"", {name});
        return false;
    }

    textures[name]->setSmooth(flag);
    
    return true;
}

Vector2 SpriteRenderer::GetLocalCenter()
{
    return localCenter;
}

Vector2 SpriteRenderer::GetGlobalCenter()
{
    return globalCenter;
}

Dictionary<String, Vector2Ptr> SpriteRenderer::GetCardinals()
{
    return cardinals;
}

#pragma endregion

#pragma region inherited

void SpriteRenderer::Init()
{
    if(transform == nullptr)
    {
        Debug.Warning("Component SpriteRenderer has no association with any GameObject");
    }
}

void SpriteRenderer::Start()
{
    if(transform == nullptr)
    {
        Debug.Warning("Component SpriteRenderer has no association with any GameObject");
    }
}

void SpriteRenderer::Render()
{
    if(transform == nullptr) return;

    Alce.GetWindow().draw(*sprite);
}

void SpriteRenderer::Update()
{
    if(transform == nullptr) return;

    sprite->setPosition(transform->position.ToPixels().ToVector2f());
    sprite->setOrigin(sprite->getLocalBounds().width / 2.0f, sprite->getLocalBounds().height / 2.0f);
    sprite->setScale((transform->scale + scale).ToVector2f());
    sprite->setRotation(transform->rotation);

    sf::Color color = sprite->getColor();
    color.a = alpha;
    sprite->setColor(color);

    RectShape bounds(sprite->getLocalBounds());
    Vector2 pixelpos = transform->position.ToPixels();

    cardinals["top-left"]->x = pixelpos.x - (bounds.width / 2.0f);
    cardinals["top-left"]->y = pixelpos.y - (bounds.height / 2.0f);

    cardinals["top-right"]->x = pixelpos.x + (bounds.width / 2.0f);
    cardinals["top-right"]->y = pixelpos.y - (bounds.height / 2.0f);

    cardinals["bottom-left"]->x = pixelpos.x - (bounds.width / 2.0f);
    cardinals["bottom-left"]->y = pixelpos.y + (bounds.height / 2.0f);

    cardinals["bottom-right"]->x = pixelpos.x + (bounds.width / 2.0f);
    cardinals["bottom-right"]->y = pixelpos.y + (bounds.height / 2.0f);
}

#pragma endregion
