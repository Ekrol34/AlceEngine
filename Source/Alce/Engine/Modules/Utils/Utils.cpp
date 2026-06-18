#include "Utils.hpp"
#include "../Color/Color.hpp"

void alce::Shell(std::string cmd)
{
    #ifdef COMPILED_IN_WINDOWS
        cmd = "powershell " + cmd;
    #endif

    system(cmd.c_str());
}

alce::String alce::OS()
{
    #ifdef COMPILED_IN_WINDOWS
        return "WINDOWS";
    #endif
    #ifdef COMPILED_IN_LINUX    
        return "LINUX";
    #endif
    #ifdef COMPILED_IN_MACOS
        return "MACOS";
    #endif
}


sf::Color alce::MapColorFromString(String colorString) 
{
    Dictionary<String, Color> colorMap = {
        {"red", alce::Colors::Red},
        {"green", alce::Colors::Green},
        {"blue", alce::Colors::Blue},
        {"white", alce::Colors::White},
        {"black", alce::Colors::Black},
        {"yellow", alce::Colors::Yellow},
        {"cyan", alce::Colors::Cyan},
        {"magenta", alce::Colors::Magenta},
        {"orange", alce::Colors::Orange},
        {"purple", alce::Colors::Purple},
        {"pink", alce::Colors::Pink},
        {"transparent", alce::Colors::Transparent}
    };

    if (colorMap.HasKey(colorString)) 
    {
        return colorMap.Get(colorString).ToSFMLColor();
    }

    if (colorString[0] == '#') 
    {
        Color hexColor(colorString);
        return hexColor.ToSFMLColor();
    }

    return sf::Color::White;
}

alce::String alce::GenerateUUID() 
{
    static std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
    static std::uniform_int_distribution<> dis(0, 15);
    static std::uniform_int_distribution<> dis2(8, 11);

    std::stringstream ss;
    int i;
    ss << std::hex;

    for (i = 0; i < 8; i++) ss << dis(gen);
    ss << "-";
    for (i = 0; i < 4; i++) ss << dis(gen);
    ss << "-4";
    for (i = 0; i < 3; i++) ss << dis(gen);
    ss << "-";
    ss << dis2(gen);
    for (i = 0; i < 3; i++) ss << dis(gen);
    ss << "-";
    for (i = 0; i < 12; i++) ss << dis(gen);
    
    return alce::String(ss.str());
}

alce::String alce::FormatString(String format, List<String> values)
{
    if(values.Length() == 0) return format;

	sf::String res = "";
	auto chain = format.Split("{}");
	int i = 0;

	for(auto& str: chain)
	{
		res += str.ToSFMLString() + values.Get(i).ToSFMLString();
		i++;
	}

	return alce::String(res);
}

alce::String alce::ConcatString(List<String> strings, String join)
{
    sf::String str = "";

	for (int i = 0; i < strings.Length(); i++)
	{
		str += strings[i].ToSFMLString();

		if (i != strings.Length() - 1) str += join.ToSFMLString();
	}

	return alce::String(str);
}

void alce::DrawDottedLine(sf::RenderTarget& target, sf::Vector2f a, sf::Vector2f b, sf::Color color, float dotLength, float gap)
{
    sf::Vector2f dir = b - a;
    float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    sf::Vector2f unit = dir / len;

    for (float i = 0; i < len; i += dotLength + gap)
    {
        sf::Vector2f start = a + unit * i;
        sf::Vector2f end = a + unit * std::min(i + dotLength, len);
        sf::Vertex line[] = { sf::Vertex(start, color), sf::Vertex(end, color) };
        target.draw(line, 2, sf::Lines);
    }
}

std::vector<sf::Vector2f> alce::ConvertShapeToPolygonPoints(ShapePtr shape)
{
    std::vector<sf::Vector2f> points;

    if (!shape) return points;

    switch (shape->GetType()) 
    {
        case ShapeType::rect: 
        {
            auto rect = std::dynamic_pointer_cast<RectShape>(shape);
            if (rect) 
            {
                sf::Vector2f pos(rect->position.x, rect->position.y);
                float w = rect->width;
                float h = rect->height;

                points.push_back(pos);
                points.push_back({pos.x + w, pos.y});
                points.push_back({pos.x + w, pos.y + h});
                points.push_back({pos.x, pos.y + h});
            }
            break;
        }

        case ShapeType::circle: 
        {
            auto circle = std::dynamic_pointer_cast<CircleShape>(shape);
            if (circle) {
                float radius = circle->radius;
                sf::Vector2f center(circle->position.x, circle->position.y);
                for (int i = 0; i < CIRCLE_QUALITY; ++i) 
                {
                    float angle = i * 2.f * Math.PI / CIRCLE_QUALITY;
                    points.emplace_back(
                        center.x + radius * std::cos(angle),
                        center.y + radius * std::sin(angle)
                    );
                }
            }
            break;
        }

        case ShapeType::polygon: 
        {
            auto poly = std::dynamic_pointer_cast<PolygonShape>(shape);
            if (poly) 
            {
                for (auto& v : poly->GetVertexList()) 
                {
                    points.emplace_back(v.x, v.y);
                }
            }
            break;
        }

        default:
            break;
    }

    return points;
}
