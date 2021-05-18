#pragma once
#include <memory>
#include <vector>
#include "BaseComponent.h"

namespace dae
{
	class Observer;
	class QBert final : public BaseComponent
	{
	public:
		explicit QBert(const std::shared_ptr<GameObject>& gameObject);

		int GetCurrentLives() const { return m_Lives; }
		void ChangeTile() const;
		void ChangeColor() const;
		void Die();

		void Update(const float deltaTime) override;

	private:
		int m_Lives{ 3 };
		int m_HP{ 100 };
		std::shared_ptr<GameObject> m_GameObject{};
	};
}


