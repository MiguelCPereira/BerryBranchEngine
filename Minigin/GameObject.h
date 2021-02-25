#pragma once
#include "BaseComponent.h"
#include "SceneObject.h"
#include "Transform.h"

namespace dae
{
	class GameObject final : public SceneObject
	{
	public:
		void Update(const float deltaTime) override;
		void Render() const override;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		GameObject() = default;
		~GameObject();
		
		GameObject(const GameObject& other)
			: m_Transform(other.m_Transform),
			m_Texture(other.m_Texture)
		{
			for (BaseComponent* baseComp : other.m_Components)
			{
				m_Components.push_back(baseComp);
			}
		};
		GameObject(GameObject&& other) noexcept
			: m_Transform(other.m_Transform),
			m_Texture(other.m_Texture)
		{
			for (BaseComponent* baseComp : other.m_Components)
			{
				m_Components.push_back(baseComp);
			}
			
			other.m_Components.clear();
			other.m_Texture = nullptr;
		};
		GameObject& operator=(const GameObject& other)
		{
			if(&other != this)
			{
				for (BaseComponent* baseComp : other.m_Components) { m_Components.push_back(baseComp); }
				m_Transform = other.m_Transform;
				m_Texture = other.m_Texture;
			}
		};
		GameObject& operator=(GameObject&& other) noexcept
		{
			if (&other != this)
			{
				for (BaseComponent* baseComp : other.m_Components) { m_Components.push_back(baseComp); }
				other.m_Components.clear();
				m_Transform = other.m_Transform;
				m_Texture = other.m_Texture;
				other.m_Texture = nullptr;
			}
		}

		void AddComponent(BaseComponent* newComponent)
		{
			m_Components.push_back(newComponent);
		}

		template<typename T>
		T* getComponent()
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
		Transform m_Transform;
		std::shared_ptr<Texture2D> m_Texture{};
	};
}
