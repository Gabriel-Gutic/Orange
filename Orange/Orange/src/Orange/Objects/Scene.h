#pragma once
#include "GameObject.h"


namespace Orange
{
	class Scene : public GameObject, public std::enable_shared_from_this<Scene>
	{
	public:
		Scene();
		~Scene() = default;

		void ShowSelectedItem();
		void ToImGuiTree();
	private:
		void ToImGuiTree(const std::shared_ptr<GameObject>& obj, int& index);
	private:
		std::unordered_set<UUID> m_SelectedItems;
		std::shared_ptr<GameObject> m_ShownItem;
	};
}
