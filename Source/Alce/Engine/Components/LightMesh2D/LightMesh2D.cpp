#include "LightMesh2D.hpp"

using namespace alce;

LightMesh2D::LightMesh2D(ShapePtr shape) : Component("LightMesh2D")
{
    this->shape = shape;
}

//Custom methods implementation
#pragma region implementation

Shape LightMesh2D::GetShape()
{
    return *shape.get();
}

bool LightMesh2D::SetShape(ShapePtr shape)
{
    if(!shape) return false;

    this->shape = shape;

    return true;
}

void LightMesh2D::SetOffset(Vector2 offset)
{
    this->offset = offset;
}

void LightMesh2D::SetOffset(float x, float y)
{
    offset = Vector2(x, y);
}

Vector2 LightMesh2D::GetOffset()
{
    return offset;
}

#pragma endregion

//Inherited methods
#pragma region inherited

void LightMesh2D::DebugRender()
{
    if(!enabled) return;

    if (auto rect = std::dynamic_pointer_cast<RectShape>(shape))
    {
        sf::Vector2f pos(rect->position.x, rect->position.y);
        float w = rect->width;
        float h = rect->height;

        sf::Vector2f a = pos;
        sf::Vector2f b = pos + sf::Vector2f(w, 0);
        sf::Vector2f c = pos + sf::Vector2f(w, h);
        sf::Vector2f d = pos + sf::Vector2f(0, h);

        DrawDottedLine(Alce.GetWindow(), a, b);
        DrawDottedLine(Alce.GetWindow(), b, c);
        DrawDottedLine(Alce.GetWindow(), c, d);
        DrawDottedLine(Alce.GetWindow(), d, a);
    }
    else if (auto circle = std::dynamic_pointer_cast<CircleShape>(shape))
    {
        sf::Vector2f center(circle->position.x, circle->position.y);
        float radius = circle->radius;
        int segments = CIRCLE_QUALITY;

        float angleStep = 2 * 3.14159265f / segments;
        for (int i = 0; i < segments; ++i)
        {
            float angle1 = i * angleStep;
            float angle2 = (i + 1) * angleStep;

            sf::Vector2f p1 = center + sf::Vector2f(std::cos(angle1), std::sin(angle1)) * radius;
            sf::Vector2f p2 = center + sf::Vector2f(std::cos(angle2), std::sin(angle2)) * radius;

            DrawDottedLine(Alce.GetWindow(), p1, p2);
        }
    }
    else if (auto poly = std::dynamic_pointer_cast<PolygonShape>(shape))
    {
        auto verts = poly->GetVertexList();
        int count = verts.Length();
        for (int i = 0; i < count; ++i)
        {
            sf::Vector2f a(verts[i].x, verts[i].y);
            sf::Vector2f b(verts[(i + 1) % count].x, verts[(i + 1) % count].y);
            DrawDottedLine(Alce.GetWindow(), a, b);
        }
    }
}

void LightMesh2D::Update()
{
    if(!enabled) return;

    Vector2 position = transform->position + offset;

    shape->position = position.ToPixels();
}



#pragma endregion