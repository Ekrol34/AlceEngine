#include "../include/Candle/LightingArea.hpp"
#include "../include/Candle/graphics/VertexArray.hpp"

#include <iostream>


namespace candle {

    
sf::BlendMode l_substractAlpha(
    sf::BlendMode::Factor::Zero,
    sf::BlendMode::Factor::One,
    sf::BlendMode::Equation::Add,
    sf::BlendMode::Factor::Zero,
    sf::BlendMode::Factor::OneMinusSrcAlpha,
    sf::BlendMode::Equation::Add
);

void LightingArea::initializeRenderTexture(const sf::Vector2f& size) {
    m_renderTexture.create(size.x, size.y);
    m_renderTexture.setSmooth(true);
}

LightingArea::LightingArea(Mode mode, const sf::Vector2f& position, const sf::Vector2f& size)
    : m_shapeVertices(sf::TriangleFan), m_color(sf::Color::White) {
    m_opacity = 1.f;
    m_mode = mode;
    m_baseTexture = nullptr;
    initializeRenderTexture(size);
    Transformable::setPosition(position);

    // Default shape: rectangle
    std::vector<sf::Vector2f> rect = {
        {0.f, 0.f},
        {size.x, 0.f},
        {size.x, size.y},
        {0.f, size.y}
    };
    setPolygonShape(rect);
}

LightingArea::LightingArea(Mode mode, const sf::Texture* t, sf::IntRect r)
    : m_shapeVertices(sf::TriangleFan), m_color(sf::Color::White) {
    m_opacity = 1.f;
    m_mode = mode;
    setAreaTexture(t, r);
}

sf::FloatRect LightingArea::getLocalBounds() const {
    return m_shapeVertices.getBounds();
}

sf::FloatRect LightingArea::getGlobalBounds() const {
    return Transformable::getTransform().transformRect(m_shapeVertices.getBounds());
}

void LightingArea::draw(sf::RenderTarget& t, sf::RenderStates s) const {
    if (m_opacity > 0.f) {
        s.transform *= getTransform();
        s.texture = &m_renderTexture.getTexture();
        s.blendMode = (m_mode == AMBIENT) ? sf::BlendAdd : sf::BlendAlpha;
        t.draw(m_shapeVertices, s);
    }
}

void LightingArea::clear() {
    m_renderTexture.clear(sf::Color(0, 0, 0, 0)); 

    if (m_baseTexture != nullptr) {
        sf::RenderStates rs;
        rs.texture = m_baseTexture;
        m_renderTexture.draw(m_shapeVertices, rs);
    } else {
        sf::VertexArray coloredShape = m_shapeVertices;
        for (std::size_t i = 0; i < coloredShape.getVertexCount(); ++i)
            coloredShape[i].color = getActualColor();

        m_renderTexture.draw(coloredShape);
    }
}

void LightingArea::setAreaColor(sf::Color c) {
    m_color = c;
    for (std::size_t i = 0; i < m_shapeVertices.getVertexCount(); ++i)
        m_shapeVertices[i].color = getActualColor();
}

sf::Color LightingArea::getAreaColor() const {
    return m_color;
}

sf::Color LightingArea::getActualColor() const {
    sf::Color ret = m_color;
    ret.a = static_cast<sf::Uint8>(m_color.a * m_opacity);
    return ret;
}

void LightingArea::setAreaOpacity(float o) {
    m_opacity = o;
    for (std::size_t i = 0; i < m_shapeVertices.getVertexCount(); ++i)
        m_shapeVertices[i].color = getActualColor();
}

float LightingArea::getAreaOpacity() const {
    return m_opacity;
}


void LightingArea::draw(const LightSource& light) {
    if (m_opacity > 0.f && m_mode == FOG) {
        sf::RenderStates fogrs;
        fogrs.blendMode = l_substractAlpha;
        fogrs.transform *= getTransform().getInverse();
        m_renderTexture.draw(light, fogrs);
    }
}

void LightingArea::setAreaTexture(const sf::Texture* texture, sf::IntRect rect) {
    m_baseTexture = texture;
    if (rect.width == 0 && rect.height == 0 && texture != nullptr) {
        rect.width = texture->getSize().x;
        rect.height = texture->getSize().y;
    }
    initializeRenderTexture({static_cast<float>(rect.width), static_cast<float>(rect.height)});
    setTextureRect(rect);
}

const sf::Texture* LightingArea::getAreaTexture() const {
    return m_baseTexture;
}

void LightingArea::setTextureRect(const sf::IntRect& rect) {
    m_baseTextureRect = rect;
    for (std::size_t i = 0; i < m_shapeVertices.getVertexCount(); ++i) {
        sf::Vector2f pos = m_shapeVertices[i].position;
        m_shapeVertices[i].texCoords = pos + sf::Vector2f(rect.left, rect.top);
    }
}

sf::IntRect LightingArea::getTextureRect() const {
    return m_baseTextureRect;
}

void LightingArea::setMode(Mode mode) {
    m_mode = mode;
}

LightingArea::Mode LightingArea::getMode() const {
    return m_mode;
}

void LightingArea::display() {
    m_renderTexture.display();
}

void LightingArea::setPolygonShape(const std::vector<sf::Vector2f>& points) {
    m_shapeVertices.setPrimitiveType(sf::TriangleFan);
    m_shapeVertices.clear();

    for (const auto& p : points) {
        sf::Vertex v;
        v.position = p;
        v.color = getActualColor();
        v.texCoords = p;
        m_shapeVertices.append(v);
    }
}

}