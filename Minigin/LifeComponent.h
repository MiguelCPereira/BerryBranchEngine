#pragma once
#include "BaseComponent.h"

namespace dae
{
	class LifeComponent : public BaseComponent
	{
	public:
		virtual ~LifeComponent() = default;
		void Update(GameObject& gameObject, Transform& transform, std::shared_ptr<Texture2D> pTexture, const float deltaTime) override;

		static void GetDamaged(int damageAmount)
		{
			if (damageAmount < 0)
			{
				std::cout << "Can't deal negative damage, to heal use the GetHealed function";
			}
			else
			{
				if (m_Health - damageAmount > 0)
				{
					m_Health -= damageAmount;
				}
				else
				{
					m_Health = 0;
					m_Alive = false;
				}
			}
		}

		static void GetHealed(int healAmount)
		{
			if (healAmount < 0)
			{
				std::cout << "Can't heal negative quantities, to deal damage use the GetDamaged function";
			}
			else
			{
				if (m_Health + healAmount > m_MaxHealth)
				{
					m_Health = m_MaxHealth;
				}
				else
				{
					m_Health += healAmount;
				}
			}
		}

	private:
		static const int m_MaxHealth;
		static int m_Health;
		static bool m_Alive;
	};

	class QBertLifeComponent final : public LifeComponent
	{
	public:
		~QBertLifeComponent() override = default;
	private:
		const int m_MaxHealth = 3;
		int m_Health = 3;
	};
}

