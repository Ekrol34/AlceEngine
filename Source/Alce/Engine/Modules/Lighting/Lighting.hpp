#pragma once

#include "../../../Libs/Libs.hpp"
#include "../Collections/Collections.hpp"
#include "../Math/Math.hpp"
#include "../Debug/Debug.hpp"
#include "../Component/Component.hpp"

namespace alce
{
    class LightingSystem
    {
    private:

        friend class GameObject;
        friend class Scene;

        candle::EdgeVector GenerateEdgesFromShape(ShapePtr shape);

        void AddLightingArea(Component* la);

        void AddLight(std::shared_ptr<candle::LightSource> light);

        void Cast();

        candle::EdgeVector edgePool;

        List<std::shared_ptr<candle::LightSource>> lights;
        List<Pair<ShapePtr, bool*>> lightMeshes;

        List<Component*> lightingAreas;
    };
}