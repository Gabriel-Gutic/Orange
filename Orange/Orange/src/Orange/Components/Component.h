#pragma once


namespace Orange
{
	class ComponentInterface
	{
	public:
		template <typename T>
		void AddComponent(const T& component);
		template <typename T, typename... Args>
		void EmplaceComponent(Args... args);
		template <typename T>
		bool HasComponent() const;
		template <typename T>
		bool RemoveComponent();
		template <typename T>
		T& GetComponent();
		template <typename T>
		const T& GetComponent() const;

		template <typename T>
		std::vector<T&> GetComponents();
		template <typename T>
		std::vector<const T&> GetComponents() const;
		template <typename T>
		bool RemoveComponents();

		std::vector<std::any>& GetAllComponents();
		const std::vector<std::any>& GetAllComponents() const;
	protected:
		std::vector<std::any> m_Components;
	};

	template<typename T>
	inline void ComponentInterface::AddComponent(const T& component)
	{
		m_Components.push_back(component);
	}

	template<typename T, typename ...Args>
	inline void ComponentInterface::EmplaceComponent(Args ...args)
	{
		AddComponent(T(args...));
	}

	template<typename T>
	inline bool ComponentInterface::HasComponent() const
	{
		for (const auto& component : m_Components)
		{
			try
			{
				std::any_cast<T>(component);
				return true;
			}
			catch (std::bad_any_cast){};
		}
		return false;
	}

	template<typename T>
	inline bool ComponentInterface::RemoveComponent()
	{
		for (int i = 0; i < m_Components.size(); i++)
		{
			try
			{
				std::any_cast<T>(m_Components[i]);
				m_Components.erase(m_Components.begin() + i);
				return true;
			}
			catch (std::bad_any_cast){};
		}

		return false;
	}

	template<typename T>
	inline T& ComponentInterface::GetComponent()
	{
		for (auto& component : m_Components)
		{
			try
			{
				return std::any_cast<T&>(component);
			}
			catch (std::bad_any_cast) {};
		}
		ORANGE_ASSERT(0, "Object does not contain a '{0}' component", T::GetName());
	}

	template<typename T>
	inline const T& ComponentInterface::GetComponent() const
	{
		for (const auto& component : m_Components)
		{
			try
			{
				return std::any_cast<const T&>(component);
			}
			catch (std::bad_any_cast) {};
		}
		ORANGE_ASSERT(0, "Object does not contain a '{0}' component", T::GetName());
	}

	template<typename T>
	inline std::vector<T&> ComponentInterface::GetComponents()
	{
		std::vector<T&> result;
		for (auto& component : m_Components)
		{
			try
			{
				result.push_back(std::any_cast<T&>(component));
			}
			catch (std::bad_any_cast) {};
		}
		return result;
	}

	template<typename T>
	inline std::vector<const T&> ComponentInterface::GetComponents() const
	{
		std::vector<T&> result;
		for (const auto& component : m_Components)
		{
			try
			{
				result.push_back(std::any_cast<const T&>(component));
			}
			catch (std::bad_any_cast) {};
		}
		return result;
	}

	template<typename T>
	inline bool ComponentInterface::RemoveComponents()
	{
		bool exist = false;
		for (int i = 0; i < m_Components.size(); )
		{
			try
			{
				std::any_cast<T>(m_Components[i]);
				m_Components.erase(m_Components.begin() + i);
				exist = true;
			}
			catch (std::bad_any_cast) 
			{
				i++;
			};
		}

		return exist;
	}
}
