#include "Image.hpp"

using namespace alce;

void Image::AddTexture(String file, String name)
{
    if(textures.HasKey(name))
    {
        Debug.Warning("[UI] Image::AddTexture -> Image already contains a texture named \"{}\"", {file});
        return;
    }
    
    auto texture = Alce.GetTexture(file);

    if(texture != nullptr)
    {
        textures.Set(name, texture);
    }
}

void Image::SetTexture(String name)
{
    if(!textures.HasKey(name))
    {
        Debug.Warning("[UI] Image::SetTexture -> Image does not contain a texture named \"{}\"", {name});
        return;
    }

    sprite->setTexture(*textures.Get(name).get());
}

void Image::RemoveTexture(String name)
{
    if(!textures.GetKeyList().Contains(name))
    {
        Debug.Warning("[UI] Image::RemoveTexture -> Image does not contain a texture named \"{}\"", {name});
        return;
    }

    textures.RemoveByKey(name);
}

void Image::SetTextureSmooth(String name, bool flag)
{
    if(!textures.GetKeyList().Contains(name))
    {
        Debug.Warning("[UI] Image::SetTextureSmooth -> Image does not contain a texture named \"{name}\"", {name});
        return;
    }

    textures[name]->setSmooth(flag);
}

void Image::Init()
{
    

}

void Image::Start()
{

}

void Image::Update()
{
    if (sprite->getTexture())
    {
        auto gb = sprite->getGlobalBounds();
        boxSize = Vector2(gb.width, gb.height);
    }

    boxPos = transform.position;

    sprite->setPosition(boxPos.ToVector2f());
    sprite->setScale(transform.scale.ToVector2f());
    sprite->setRotation(transform.rotation);
}

void Image::Render()
{
    if (borderRadius > 0)
    {
        int totalPoints = CIRCLE_QUALITY * 4;

        sf::ConvexShape roundedBox;
        roundedBox.setPointCount(totalPoints);

        float step = 90.f / CIRCLE_QUALITY;
        int index = 0;

        auto addCorner = [&](float cx, float cy, float startAng)
        {
            for (int i = 0; i < CIRCLE_QUALITY; i++, index++)
            {
                float ang = (startAng + i * step) * 0.0174532925f;
                float x = cx + borderRadius * cos(ang);
                float y = cy + borderRadius * sin(ang);
                roundedBox.setPoint(index, sf::Vector2f(x, y));
            }
        };

        addCorner(boxSize.x - borderRadius, borderRadius, -90);
        addCorner(boxSize.x - borderRadius, boxSize.y - borderRadius, 0);
        addCorner(borderRadius, boxSize.y - borderRadius, 90);
        addCorner(borderRadius, borderRadius, 180);

        roundedBox.setPosition(boxPos.ToVector2f());
        roundedBox.setFillColor(backgroundColor.ToSFMLColor());
        roundedBox.setOutlineThickness(borderWidth);
        roundedBox.setOutlineColor(borderColor.ToSFMLColor());

        Alce.GetWindow().draw(roundedBox);
    }
    else
    {
        sf::RectangleShape rect;
        rect.setPosition(boxPos.ToVector2f());
        rect.setSize(boxSize.ToVector2f());
        rect.setFillColor(backgroundColor.ToSFMLColor());
        rect.setOutlineColor(borderColor.ToSFMLColor());
        rect.setOutlineThickness(borderWidth);

        Alce.GetWindow().draw(rect);
    }

    Alce.GetWindow().draw(*sprite);
}

void Image::EventManager(sf::Event& event)
{

}