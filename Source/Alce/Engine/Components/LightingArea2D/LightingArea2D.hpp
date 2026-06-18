#pragma once

#include "../../Modules/Modules.hpp"

namespace alce
{
	class LightingArea2D : public Component
	{
	public:

		LightingArea2D();

		void SetSize(Vector2 size);

		void SetSize(float width, float height);

		void SetOffset(Vector2 offset);

		void SetOffset(float x, float y);

		Vector2 GetOffset();

		bool SetOpacity(float opacity);

		float GetOpacity();

		void Init();

		void Start();

		void Render();

		void DebugRender();

		void Update();

		Color color = Colors::Black;


	private:

		friend class GameObject;
		friend class LightingSystem;

		bool compute = false;
		Vector2 size = Vector2(100, 100);
		Vector2 offset = Vector2(0, 0);

		float opacity = 1.0f;

		std::shared_ptr<candle::LightingArea> lightingArea = nullptr;
		List<std::shared_ptr<candle::LightSource>> lights;

	};

	typedef std::shared_ptr<LightingArea2D> LightingArea2DPtr;
}