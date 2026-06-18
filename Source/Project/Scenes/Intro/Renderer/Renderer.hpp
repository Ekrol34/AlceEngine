#pragma once

#include "../Intro.hpp"

using namespace alce;

namespace IntroScene
{
	class Renderer : public GameObject
	{
	public:

		Renderer();

		void Init();

		void Start();

		void Update();

		void SetterManager(String name, String value);

		String GetterManager(String name);

	private:

		CameraPtr camera;
		SpriteRendererPtr spriteRenderer;
		TextRendererPtr textRenderer;

		int step = 0;

		float elapsed;

	};

	typedef std::shared_ptr<Renderer> RendererPtr;
}