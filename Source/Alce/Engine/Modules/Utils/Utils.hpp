#pragma once

#if defined(__linux__) || defined(__linux) || defined(linux) || defined(__gnu_linux__)
    #define COMPILED_IN_LINUX
#elif defined(__APPLE__) && defined(__MACH__)
    #define COMPILED_IN_MACOS
#elif defined(_WIN32) || defined(_WIN64)
    #define COMPILED_IN_WINDOWS
#endif

#include <stdlib.h>
#include <random>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <chrono>

#include "../FileSystem/FileSystem.hpp"
#include "../String/String.hpp"
#include "../Math/Math.hpp"

namespace alce
{
    void Shell(std::string cmd);
    
    String OS();

    String GenerateUUID();

    String FormatString(String format, List<String> values);

    String ConcatString(List<String> strings, String join = "");

    void DrawDottedLine(sf::RenderTarget& target, sf::Vector2f a, sf::Vector2f b, sf::Color color = sf::Color::Red, float dotLength = 5.f, float gap = 5.f);

    std::vector<sf::Vector2f> ConvertShapeToPolygonPoints(ShapePtr shape);

    sf::Color MapColorFromString(String colorString);

    template<typename T>
    List<T> MergeLists(List<List<T>> lists)
    {
        if(lists.IsEmpty()) return {};

        List<T> result = lists.First();

        for(int i = 1; i < lists.Length(); i++)
        {
            result.Merge(lists[i]);
        }

        return result;
    }
}