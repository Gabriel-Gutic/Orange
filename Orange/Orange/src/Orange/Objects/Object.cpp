#include "pchOrange.h"
#include "Object.h"

#include <imgui/imgui.h>


namespace Orange
{
	Object::Object(std::string_view name, const UUID& uuid)
		:m_Name(name), m_UUID(uuid)
	{
	}

	const UUID& Object::GetUUID() const
	{
		return m_UUID;
	}

	void Object::SetName(std::string_view name)
	{
		m_Name = name;
	}

	const std::string& Object::GetName() const
	{
		return m_Name;
	}

	std::string Object::ToString() const
	{
		return "<Object: '" + m_Name + "' ID='" + m_UUID.ToString() + "'>";
	}

	Transform& Object::GetTransform()
	{
		return m_Transform;
	}

	const Transform& Object::GetTransform() const
	{
		return m_Transform;
	}

	const std::vector<std::shared_ptr<Object>>& Object::GetChildren() const
	{
		return m_Children;
	}

	std::vector<std::shared_ptr<Object>>& Object::GetChildren()
	{
		return m_Children;
	}

	void Object::PushChild(const std::shared_ptr<Object>& child)
	{
		m_Children.push_back(child);
	}

	void Object::InsertChild(const std::shared_ptr<Object>& child, uint32_t index)
	{
		m_Children.insert(m_Children.begin() + index, child);
	}

	void Object::PopChild()
	{
		m_Children.pop_back();
	}

	void Object::RemoveChild(std::string_view name)
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

	void Object::RemoveChild(uint32_t index)
	{
		m_Children.erase(m_Children.begin() + index);
	}

	void Object::ToImGuiTree() const
	{
		int i = -1;
		ToImGuiTree(i);
	}

	void Object::ToImGuiTree(int& i) const
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