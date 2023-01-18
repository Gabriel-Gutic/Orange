#pragma once


namespace Orange
{
	class Object
	{
	public:
		Object() = default;
		virtual ~Object() = default;

		void SetName(std::string_view name);
		const std::string& GetName() const;

		Transform& GetTransform();
		const Transform& GetTransform() const;
	protected:
		std::string m_Name;
		Transform m_Transform;
	};
}