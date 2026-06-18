#pragma once

#include "../../../Alce/Alce.hpp"

using namespace alce;

namespace SharedScene
{
	class Shared : public Scene
	{
	public:

		Shared();

		void Init();

		void Start();

	};

	typedef std::shared_ptr<Shared> SharedPtr;
}