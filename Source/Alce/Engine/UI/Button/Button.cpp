#include "Button.hpp"

using namespace alce;

void Button::Init()
{

}

void Button::Start()
{

}

void Button::Update()
{
    Vector2 size = Vector2(richText.getLocalBounds().width, richText.getLocalBounds().height) + (padding * 2);

    box.setPosition(transform.position.x, transform.position.y);
    box.setSize(size.ToVector2f());

    sf::Color fillColor = isMouseOver
        ? (isMousePressed ? onClickBackgroundColor.ToSFMLColor() : mouseOverBackgroundColor.ToSFMLColor())
        : backgroundColor.ToSFMLColor();

    if (borderRadius > 0)
    {
        int totalPoints = CIRCLE_QUALITY * 4;

        roundedBox.setPointCount(totalPoints);

        float angleStep = 90.f / CIRCLE_QUALITY;
        int pointIndex = 0;

        auto addCorner = [&](float cx, float cy, float startAngle) {
            for (int i = 0; i < CIRCLE_QUALITY; ++i, ++pointIndex)
            {
                float angle = startAngle + i * angleStep;
                float rad = angle * (3.14159f / 180.f);
                float x = cx + borderRadius * cos(rad);
                float y = cy + borderRadius * sin(rad);
                roundedBox.setPoint(pointIndex, sf::Vector2f(x, y));
            }
        };

        addCorner(size.x - borderRadius, borderRadius, -90);
        addCorner(size.x - borderRadius, size.y - borderRadius, 0);
        addCorner(borderRadius, size.y - borderRadius, 90);
        addCorner(borderRadius, borderRadius, 180);

        roundedBox.setPosition(box.getPosition());
        roundedBox.setFillColor(fillColor);
        roundedBox.setOutlineThickness(borderWidth);
        roundedBox.setOutlineColor(borderColor.ToSFMLColor());
    }
    else
    {
        box.setFillColor(fillColor);
        box.setOutlineThickness(borderWidth);
        box.setOutlineColor(borderColor.ToSFMLColor());
    }

    _font = *Alce.GetFont(font).get();
    richText.setFont(_font);
    richText.setCharacterSize(fontSize);

    richText.clear();
    richText << text.ToSFMLString();

    sf::FloatRect textBounds = richText.getLocalBounds();
    richText.setOrigin(textBounds.left + textBounds.width / 2.0f,
                    textBounds.top + textBounds.height / 2.0f);
    float offsetY = (richText.getCharacterSize() - textBounds.height) / 2.0f;
    richText.setPosition(transform.position.x + size.x / 2.0f,
                        transform.position.y + size.y / 2.0f + offsetY);


    richText.setCharacterSize(fontSize);
}

void Button::Render()
{
    if(borderRadius > 0)
    {
        Alce.GetWindow().draw(roundedBox);
    }
    else
    {   
        Alce.GetWindow().draw(box);
    }

    richText.clear();
    richText << (isMouseOver ? mouseOverTextColor.ToSFMLColor() : textColor.ToSFMLColor()) << text.ToSFMLString();
    Alce.GetWindow().draw(richText);
}

void Button::EventManager(sf::Event& event)
{
    Vector2 mousePos = Alce.GetWindow().mapPixelToCoords(sf::Mouse::getPosition(Alce.GetWindow()));
    bool wasMouseOver = isMouseOver; 
    isMouseOver = box.getGlobalBounds().contains(mousePos.x, mousePos.y);

    sf::Cursor cursor;

    if (isMouseOver)
    {
        if (!wasMouseOver && onMouseEnter)
        {
            onMouseEnter();
        }

        if (cursor.loadFromSystem(sf::Cursor::Hand))
        {
            Alce.GetWindow().setMouseCursor(cursor);
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            isOnClick = true;
            isMousePressed = true;
            if (onClick)
            {
                onClick();
            }
        }

        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
        {
            isMousePressed = false;
        }
    }
    else
    {
        if (wasMouseOver)
        {
            if (onMouseOut)
            {
                onMouseOut();
            }

            if (cursor.loadFromSystem(sf::Cursor::Arrow))
            {
                Alce.GetWindow().setMouseCursor(cursor);
            }
        }

        isOnClick = false;
        isMousePressed = false;
    }
}

