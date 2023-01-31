#pragma once
#include "Event/Event.h"


namespace Orange
{
	class Layer
	{
	protected:
		Layer() = default;
	public:
		virtual void OnUpdate(float dt) {}
		virtual void OnEvent(const Event& e) {}
		virtual void OnImGui() {}
	};
}
