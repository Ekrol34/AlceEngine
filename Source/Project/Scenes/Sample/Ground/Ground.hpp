#pragma once

#include "../Sample.hpp"

using namespace alce;

namespace SampleScene
{
	class Ground : public GameObject
	{
	public:

		Ground();

		void Init();

		void Start();

		void Update();

		void SetterManager(String name, String value);

	private:

		Rigidbody2DPtr rigidbody2d;
		TileMapPtr tilemap;

		TextRendererPtr textRenderer;
	};
	typedef std::shared_ptr<Ground> GroundPtr;
}