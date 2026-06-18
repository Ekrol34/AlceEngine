#include "Lighting.hpp"
#include "../../Components/LightingArea2D/LightingArea2D.hpp"

using namespace alce;

candle::EdgeVector LightingSystem::GenerateEdgesFromShape(ShapePtr shape)
{
    candle::EdgeVector edges;

    if(!shape)
    {
        return edges;
    }

    sf::Vector2f pos(shape->position.x, shape->position.y);

    switch (shape->GetType())
    {
        case ShapeType::rect:
        {
            auto rect = std::static_pointer_cast<RectShape>(shape);
            float w = rect->width;
            float h = rect->height;

            sf::Vector2f p1 = pos;
            sf::Vector2f p2 = pos + sf::Vector2f(w, 0);
            sf::Vector2f p3 = pos + sf::Vector2f(w, h);
            sf::Vector2f p4 = pos + sf::Vector2f(0, h);

            edges.emplace_back(p1, p2);
            edges.emplace_back(p2, p3);
            edges.emplace_back(p3, p4);
            edges.emplace_back(p4, p1);
            break;
        }

        case ShapeType::polygon:
        {
            auto poly = std::static_pointer_cast<PolygonShape>(shape);
            List<Vector2> verts = poly->GetVertexList();

            for (size_t i = 0; i < verts.Length(); ++i)
            {
                Vector2 a = verts[i] + shape->position;
                Vector2 b = verts[(i + 1) % verts.Length()] + shape->position;

                sf::Vector2f p1(a.x, a.y);
                sf::Vector2f p2(b.x, b.y);

                edges.emplace_back(p1, p2);
            }
            break;
        }

        case ShapeType::circle:
        {
            auto circle = std::static_pointer_cast<CircleShape>(shape);
            const int segments = CIRCLE_QUALITY;
            float r = circle->radius;

            for (int i = 0; i < segments; ++i)
            {
                float angle1 = (2 * Math.PI * i) / segments;
                float angle2 = (2 * Math.PI * (i + 1)) / segments;

                sf::Vector2f p1 = pos + sf::Vector2f(std::cos(angle1), std::sin(angle1)) * r;
                sf::Vector2f p2 = pos + sf::Vector2f(std::cos(angle2), std::sin(angle2)) * r;

                edges.emplace_back(p1, p2);
            }
            break;
        }

        default:
            break;
    }

    return edges;
}

void LightingSystem::AddLightingArea(Component* la)
{
    if(la->GetId() != "LightingArea2D") return;

    lightingAreas.Add(la);

    ((LightingArea2D*) la)->lights = this->lights;
}

void LightingSystem::AddLight(std::shared_ptr<candle::LightSource> light)
{
    if(light == nullptr) return;

    lights.Add(light);

    for(auto& la: lightingAreas)
    {
        ((LightingArea2D*) la)->lights.Add(light);
    }
}

void LightingSystem::Cast()
{
    edgePool.clear();

    for(auto& shape: lightMeshes)
    {
        if(!*shape.second) continue;

        auto edges = GenerateEdgesFromShape(shape.first);
        
        for(auto& edge: edges)
        {
            edgePool.push_back(edge);
        }
    }

    lights.RemoveIf([](std::shared_ptr<candle::LightSource> light) {
        return light->destroy;
    });

    for(auto& light: lights)
    {
        light->castLight(edgePool.begin(), edgePool.end());
    }
}