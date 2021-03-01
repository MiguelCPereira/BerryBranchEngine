#pragma once
#include "BaseComponent.h"
#include "GameDisplays.h"

namespace dae
{
	class LifeComponent : public BaseComponent
	{
	public:
		virtual ~LifeComponent() = default;
		virtual void Initialize() override;
		void Update(GameObject& gameObject, Transform& transform, std::shared_ptr<Texture2D> pTexture, const float deltaTime) override;

		virtual void GetDamaged(int damageAmount);

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
		std::unique_ptr<Subject> m_Subject;
	};

	class QBertLifeComponent final : public LifeComponent
	{
	public:
		~QBertLifeComponent() override
		{
			delete m_Subject;
			m_Subject = nullptr;
		}

		void Initialize() override
		{
			m_Subject = new Subject;
			Observer* observer = new GameDisplays;
			m_Subject->AddObserver(observer);
		}

		void GetDamaged(int damageAmount) override
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
					m_Subject->Notify(*this, Event::ActorDied);
				}
			}
		}
	private:
		const int m_MaxHealth = 3;
		int m_Health = 3;
		bool m_Alive = true;
		Subject* m_Subject;
	};
}

