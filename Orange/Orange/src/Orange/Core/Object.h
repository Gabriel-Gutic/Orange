#pragma once


namespace Orange
{
	class Object
	{
	public:
		Object() = default;
		virtual ~Object() = default;
	protected:
		std::string m_Name;
	};
}