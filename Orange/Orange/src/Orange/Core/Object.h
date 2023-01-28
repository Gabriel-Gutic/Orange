#pragma once


namespace Orange
{
	class Object
	{
	public:
		Object(std::string_view name = "Object");
		virtual ~Object() = default;

		void SetName(std::string_view name);
		const std::string& GetName() const;

		virtual std::string ToString() const;

		Transform& GetTransform();
		const Transform& GetTransform() const;

		const std::vector<std::shared_ptr<Object>>& GetChildren() const;
		std::vector<std::shared_ptr<Object>>& GetChildren();

		void ToImGuiTree() const;
	protected:
		std::string m_Name;
		Transform m_Transform;

		std::vector<std::shared_ptr<Object>> m_Children;
	};
}