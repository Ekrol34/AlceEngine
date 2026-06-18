#pragma once

#include "../../Modules/Modules.hpp"

namespace alce
{
	class LightMesh2D : public Component
	{
	public:

		LightMesh2D(ShapePtr shape);

		Shape GetShape();

		bool SetShape(ShapePtr shape);

		void SetOffset(Vector2 offset);

		void SetOffset(float x, float y);

		Vector2 GetOffset();

		void DebugRender();

		void Update();

	private:

		friend class GameObject;

		Vector2 offset = Vector2(0, 0);
		ShapePtr shape;
	};

	typedef std::shared_ptr<LightMesh2D> LightMesh2DPtr;
}