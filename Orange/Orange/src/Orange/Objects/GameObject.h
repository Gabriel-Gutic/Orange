#pragma once
#include "Core/UUID.h"
#include "Components/Component.h"


namespace Orange
{
	class GameObject : public ComponentInterface
	{
	public:
		GameObject(std::string_view name = "GameObject", const UUID& uuid = UUID());
		virtual ~GameObject() = default;

		const UUID& GetUUID() const;

		void SetName(std::string_view name);
		const std::string& GetName() const;

		virtual std::string ToString() const;

		Transform& GetTransform();
		const Transform& GetTransform() const;

		const std::vector<std::shared_ptr<GameObject>>& GetChildren() const;
		std::vector<std::shared_ptr<GameObject>>& GetChildren();

		void PushChild(const std::shared_ptr<GameObject>& child);
		void InsertChild(const std::shared_ptr<GameObject>& child, uint32_t index);
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

		std::vector<std::shared_ptr<GameObject>> m_Children;

		static int s_TreeID;
	};
}


namespace std
{
	template <>
	struct hash<Orange::GameObject>
	{
		size_t operator() (const Orange::GameObject& obj) const
		{
			const Orange::UUID& uuid = obj.GetUUID();
			return hash<Orange::UUID>()(uuid);
		}
	};
}