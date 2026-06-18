#pragma once

#include <memory>

#include "../Math/Math.hpp"

namespace alce
{
    class Transform2 
    {
    public:

        Vector2 position = Vector2(0.0f, 0.0f);

        Vector2 scale = Vector2(1.0f, 1.0f);

        float rotation = 0.0f;

        void Reset()
        {
            position = Vector2(0.0f, 0.0f);
            scale = Vector2(1.0f, 1.0f);
            rotation = 0.0f;
        }  
    };

    typedef std::shared_ptr<Transform2> Transform2Ptr;

    class Transform3
    {
    public:

        Vector3 position = Vector3(0.0f, 0.0f, 0.0f);

        Vector3 scale = Vector3(1.0f, 1.0f, 1.0f);

        float rotation = 0.0f;

        void Reset()
        {
            position = Vector3(0.0f, 0.0f, 0.0f);
            scale = Vector3(1.0f, 1.0f, 1.0f);
            rotation = 0.0f;
        }  
    };

    typedef std::shared_ptr<Transform3> Transform3Ptr;
}