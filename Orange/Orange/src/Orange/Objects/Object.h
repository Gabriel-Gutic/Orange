#pragma once
#include "Core/UUID.h"


namespace Orange
{
	class Object
	{
	public:
		Object(std::string_view name = "Object", const UUID& uuid = UUID());
		virtual ~Object() = default;

		const UUID& GetUUID() const;

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
	private:
		void ToImGuiTree(int& i) const;
	protected:
		UUID m_UUID;
		std::string m_Name;
		Transform m_Transform;

		std::vector<std::shared_ptr<Object>> m_Children;

		static int s_TreeID;
	};
}


namespace std
{
	template <>
	struct hash<Orange::Object>
	{
		size_t operator() (const Orange::Object& obj) const
		{
			const Orange::UUID& uuid = obj.GetUUID();
			return hash<Orange::UUID>()(uuid);
		}
	};
}