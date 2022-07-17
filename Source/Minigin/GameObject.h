#pragma once
#include <vector>
#include "MiniginLibType.h"

namespace dae
{
	class BaseComponent;
	class Transform;

	class GameObject final
	{
	public:
		void Initialize();
		void Update(const float deltaTime);
		void Render() const;

		void SetPosition(float x, float y) const;
		void MINIGIN_ENTRY RemoveAllComponents();

		GameObject() = default;
		MINIGIN_ENTRY ~GameObject();
		
		GameObject(const GameObject& other)
			: m_Transform(other.m_Transform)
		{
			for (BaseComponent* baseComp : other.m_Components)
			{
				m_Components.push_back(baseComp);
			}
		};
		GameObject(GameObject&& other) noexcept
			: m_Transform(other.m_Transform)
		{
			for (BaseComponent* baseComp : other.m_Components)
			{
				m_Components.push_back(baseComp);
			}
			
			other.m_Components.clear();
		};
		GameObject& operator=(const GameObject& other)
		{
			if(&other != this)
			{
				for (BaseComponent* baseComp : other.m_Components) { m_Components.push_back(baseComp); }
				//m_Transform = other.m_Transform;
			}
		};
		GameObject& operator=(GameObject&& other) noexcept
		{
			if (&other != this)
			{
				for (BaseComponent* baseComp : other.m_Components) { m_Components.push_back(baseComp); }
				other.m_Components.clear();
				//m_Transform = other.m_Transform;
			}
		}

		void MINIGIN_ENTRY AddComponent(BaseComponent* newComponent);

		template<typename T>
		T* GetComponent()
		{
			for (BaseComponent* baseComp : m_Components)
			{
				if (dynamic_cast<T*>(baseComp))
					return(T*)baseComp;
			}
			
			return nullptr;
		}

	private:
		std::vector<BaseComponent*> m_Components{};
		Transform* m_Transform{};
		bool m_ComponentsRemoved{ false };
	};
}
