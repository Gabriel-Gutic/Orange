#pragma once
#include "Event/Event.h"


namespace Orange
{
	class Layer
	{
	protected:
		Layer() = default;
	public:
		virtual void OnUpdate() {}
		virtual void OnEvent(const Event& e) {}
	};
}
