#include "pchOrange.h"
#include "Component.h"


namespace Orange
{
	std::vector<std::any>& ComponentInterface::GetAllComponents()
	{
		return m_Components;
	}

	const std::vector<std::any>& ComponentInterface::GetAllComponents() const
	{
		return m_Components;
	}
}