#include "pchOrange.h"
#include "Object.h"

#include <imgui/imgui.h>


namespace Orange
{
	Object::Object(std::string_view name)
		:m_Name(name)
	{
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
		return "<Object: '" + m_Name + "'>";
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

	void Object::ToImGuiTree() const
	{
		if (ImGui::TreeNode(m_Name.c_str()))
		{
			for (const auto& child : m_Children)
			{
				child->ToImGuiTree();
			}
			ImGui::TreePop();
		}
	}
}