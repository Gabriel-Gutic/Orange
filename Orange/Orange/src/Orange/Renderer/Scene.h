#pragma once
#include "Core/Object.h"


namespace Orange
{
	class Scene : public Object
	{
	public:
		Scene();
		~Scene() = default;

		virtual void Draw() override;
	private:
	};
}
