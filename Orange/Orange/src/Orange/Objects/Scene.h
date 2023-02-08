#pragma once
#include "Object.h"


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
