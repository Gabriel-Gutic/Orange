#include "pchOrange.h"
#include "GameObject.h"

#include <imgui/imgui.h>


namespace Orange
{
	GameObject::GameObject(std::string_view name, const UUID& uuid)
		:m_Name(name), m_UUID(uuid), m_DrawFunction([](const GameObject&){})
	{
	}

	const UUID& GameObject::GetUUID() const
	{
		return m_UUID;
	}

	void GameObject::SetName(std::string_view name)
	{
		m_Name = name;
	}

	const std::string& GameObject::GetName() const
	{
		return m_Name;
	}

	std::string GameObject::ToString() const
	{
		return "<GameObject: '" + m_Name + "' ID='" + m_UUID.ToString() + "'>";
	}

	Transform& GameObject::GetTransform()
	{
		return m_Transform;
	}

	const Transform& GameObject::GetTransform() const
	{
		return m_Transform;
	}

	const std::vector<std::shared_ptr<GameObject>>& GameObject::GetChildren() const
	{
		return m_Children;
	}

	std::vector<std::shared_ptr<GameObject>>& GameObject::GetChildren()
	{
		return m_Children;
	}

	void GameObject::PushChild(const std::shared_ptr<GameObject>& child)
	{
		m_Children.push_back(child);
	}

	void GameObject::InsertChild(const std::shared_ptr<GameObject>& child, uint32_t index)
	{
		m_Children.insert(m_Children.begin() + index, child);
	}

	void GameObject::PopChild()
	{
		m_Children.pop_back();
	}

	void GameObject::RemoveChild(std::string_view name)
	{
		uint32_t i = 0;
		while (i < m_Children.size())
		{
			if (m_Children[i]->GetName() == name)
				RemoveChild(i);
			else
				i++;
		}
	}

	void GameObject::RemoveChild(uint32_t index)
	{
		m_Children.erase(m_Children.begin() + index);
	}

	void GameObject::ToImGuiTree() const
	{
		int i = -1;
		ToImGuiTree(i);
	}

	void GameObject::Draw()
	{
		m_DrawFunction(*this);
	}

	void GameObject::SetDrawFunction(const std::function<void(const GameObject&)>& func)
	{
		m_DrawFunction = func;
	}

	void GameObject::ToImGuiTree(int& i) const
	{
		i++;
		if (m_Children.size() <= 0)
		{
			ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen; // ImGuiTreeNodeFlags_Bullet
			ImGui::TreeNodeEx((void*)(intptr_t)i, node_flags, m_Name.c_str(), i);
		}
		else
		{
			if (ImGui::TreeNode(m_Name.c_str()))
			{
				for (const auto& child : m_Children)
				{
					child->ToImGuiTree(i);
				}
				ImGui::TreePop();
			}
		}
	}
}