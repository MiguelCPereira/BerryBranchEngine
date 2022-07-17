#pragma once
#include "BaseComponent.h"

namespace dae
{
	class LifeComponent final : public BaseComponent
	{
	public:
		LifeComponent(int maxHP);
		virtual ~LifeComponent() = default;

		LifeComponent(const LifeComponent& other) = delete;
		LifeComponent(LifeComponent&& other) = delete;
		LifeComponent& operator=(const LifeComponent& other) = delete;
		LifeComponent& operator=(LifeComponent&& other) = delete;
		
		void Update(const float deltaTime) override;
		int GetHP() const { return m_Health; }
		void GetDamaged(int damageAmount);
		void GetHealed(int healAmount);

	private:
		const int m_MaxHealth;
		int m_Health;
		bool m_Alive;
	};
}

