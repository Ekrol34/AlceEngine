#pragma once

#include "../Shared.hpp"

using namespace alce;

namespace SharedScene
{
	class Player : public GameObject
	{
	public:

		Player();

		void Init();

		void Start();

		void OnCollisionEnter(GameObject* other)
		{
			if(other->HasTag("particle"))
			{
				Debug.Log("Contacto con particula");
			}
		}

		void OnImpact(GameObject* other);

		void OnImpactEnd(GameObject* other);

		void SetterManager(String name, String value);

		String GetterManager(String name);

		void Update();


	private:

		CameraPtr camera;
		Rigidbody2DPtr rigidbody2d;
		Animation2dPtr animation;
		Raycast2DPtr leftRaycast2d;
		Raycast2DPtr rightRaycast2d;
		CanvasPtr canvas;
		SpriteRendererPtr backgroundRenderer;

		ParticleSystemPtr ps;

		Light2DPtr light;
		AnimationPtr anima;

		void AnimationManager();

		float velocity;
		float walkSpeed;
		float runSpeed;
		bool grounded;
		bool walking;
		bool jumping;
		bool running;

		String status;
	};
	
	typedef std::shared_ptr<Player> PlayerPtr;
}