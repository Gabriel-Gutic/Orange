#include "pchOrange.h"
#include "Scene.h"


namespace Orange
{
	Scene::Scene()
		:GameObject("Scene")
	{
		m_Children.push_back(std::make_shared<Camera>());
	
		SetDrawFunction([](const GameObject& obj) {
			for (auto& child : obj.GetChildren())
				child->Draw();
		});
	}
}