/**
 * @file
 * @author Miguel Mejía Jiménez
 * @copyright MIT License
 * @brief This file contains the LightingArea class.
 */
#ifndef __CANDLE_LIGHTING_HPP__
#define __CANDLE_LIGHTING_HPP__

#include <set>

#include <SFML/Graphics.hpp>

#include "geometry/Line.hpp"
#include "LightSource.hpp"
#include "../../../../Engine/Modules/Math/Math.hpp"

namespace candle {

    class LightingArea : public sf::Transformable, public sf::Drawable {
public:
    enum Mode {
        FOG,
        AMBIENT
    };

private:
    const sf::Texture* m_baseTexture;
    sf::IntRect m_baseTextureRect;
    sf::RenderTexture m_renderTexture;

    sf::VertexArray m_shapeVertices;   // Lighting area polygon
    sf::Color m_color;
    float m_opacity;
    Mode m_mode;

    void draw(sf::RenderTarget&, sf::RenderStates) const override;
    sf::Color getActualColor() const;
    void initializeRenderTexture(const sf::Vector2f& size);

public:
    LightingArea(Mode mode, const sf::Vector2f& position, const sf::Vector2f& size);
    LightingArea(Mode mode, const sf::Texture* texture, sf::IntRect rect = sf::IntRect());

    sf::FloatRect getLocalBounds() const;
    sf::FloatRect getGlobalBounds() const;

    void setAreaColor(sf::Color color);
    sf::Color getAreaColor() const;

    void setAreaOpacity(float opacity);
    float getAreaOpacity() const;

    void setAreaTexture(const sf::Texture* texture, sf::IntRect rect = sf::IntRect());
    const sf::Texture* getAreaTexture() const;

    void setTextureRect(const sf::IntRect& rect);
    sf::IntRect getTextureRect() const;

    void setMode(Mode mode);
    Mode getMode() const;

    void clear();
    void draw(const LightSource& light);
    void display();

    // New Method
    void setPolygonShape(const std::vector<sf::Vector2f>& points);
};
}


#endif
