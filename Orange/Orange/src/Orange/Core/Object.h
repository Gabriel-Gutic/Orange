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

		void PushChild(const std::shared_ptr<Object>& child);
		void InsertChild(const std::shared_ptr<Object>& child, uint32_t index);
		void PopChild();
		void RemoveChild(std::string_view name);
		void RemoveChild(uint32_t index);

		void ToImGuiTree() const;

		virtual void Draw(){}
	protected:
		std::string m_Name;
		Transform m_Transform;

		std::vector<std::shared_ptr<Object>> m_Children;

		static int s_TreeID;
	};
}