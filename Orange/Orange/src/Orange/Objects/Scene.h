#pragma once
#include "GameObject.h"


namespace Orange
{
	class Scene : public GameObject
	{
	public:
		Scene();
		~Scene() = default;

		virtual void Draw() override;
	private:
	};
}
