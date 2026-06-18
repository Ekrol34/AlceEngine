#pragma once

#include "../../../Alce/Alce.hpp"

using namespace alce;

namespace IntroScene
{
	class Intro : public Scene
	{
	public:

		Intro();

		void Init();

		void Start();

	};

	typedef std::shared_ptr<Intro> IntroPtr;
}