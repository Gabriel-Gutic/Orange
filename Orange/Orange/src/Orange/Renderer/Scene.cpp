#include "pchOrange.h"
#include "Scene.h"


namespace Orange
{
	Scene::Scene()
		:Object("Scene")
	{
		m_Children.push_back(std::make_shared<Camera>());
	}

	void Scene::Draw()
	{
		for (auto& child : m_Children)
			child->Draw();
	}
}