#include "pchOrange.h"
#include "Scene.h"

#include <imgui/imgui.h>


namespace Orange
{
	Scene::Scene()
		:GameObject("Scene"), m_ShownItem(nullptr)
	{
		m_Children.push_back(std::make_shared<Camera>());
		
		SetDrawFunction([](const GameObject& obj) {
			for (auto& child : obj.GetChildren())
				child->Draw();
		});
	}

	void Scene::ShowSelectedItem()
	{
		if (m_ShownItem)
		{
			GameObject& obj = *m_ShownItem;

			obj.GetTransform().ToImGui();
		}
	}

	void Scene::ToImGuiTree()
	{
		int i = -1;
		ToImGuiTree(shared_from_this(), i);
	}

	void Scene::ToImGuiTree(const std::shared_ptr<GameObject>& obj, int& index)
	{
		index++;
		int index_copy = index;

		ImGuiTreeNodeFlags node_flags = {};
		bool clicked = false;

		if (m_SelectedItems.find(obj->GetUUID()) != m_SelectedItems.end())
			node_flags |= ImGuiTreeNodeFlags_Selected;
		if (obj->GetChildren().size() <= 0)
		{
			node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen; // ImGuiTreeNodeFlags_Bullet
			ImGui::TreeNodeEx((void*)(intptr_t)index, node_flags, obj->GetName().c_str(), index);
			if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
				clicked = true;
		}
		else
		{
			bool opened = ImGui::TreeNodeEx((void*)(intptr_t)index, node_flags, obj->GetName().c_str(), index);

			if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
				clicked = true;
			if (opened)
			{
				for (const auto& child : obj->GetChildren())
				{
					ToImGuiTree(child, index);
				}
				ImGui::TreePop();
			}
		}

		if (clicked)
		{
			if (!ImGui::GetIO().KeyCtrl)
			{
				m_SelectedItems.clear();
				m_ShownItem = obj;
			}
			UUID uuid = obj->GetUUID();
			if (m_SelectedItems.find(uuid) == m_SelectedItems.end())
				m_SelectedItems.insert(uuid);
		}
	}
}