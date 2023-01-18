#include "pchOrange.h"
#include "Object.h"


namespace Orange
{
	void Object::SetName(std::string_view name)
	{
		m_Name = name;
	}

	const std::string& Object::GetName() const
	{
		return m_Name;
	}

	Transform& Object::GetTransform()
	{
		return m_Transform;
	}

	const Transform& Object::GetTransform() const
	{
		return m_Transform;
	}
}