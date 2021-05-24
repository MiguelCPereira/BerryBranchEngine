#pragma once
#include <vector>
#include "BaseComponent.h"


// This class isn't the one I use in the game for QBert
// This is just here for the sake of the Engine Demo
// (the assignments we did throughout the semester)


namespace dae
{
	class Observer;
	class QBertComponent final : public BaseComponent
	{
	public:
		explicit QBertComponent(const std::shared_ptr<GameObject>& gameObject);

		int GetCurrentLives() const { return m_Lives; }
		void ChangeTile() const;
		void ChangeColor() const;
		void Die();

		void Update(const float deltaTime) override;
	
	private:
		int m_Lives{3};
		int m_HP{100};
		std::shared_ptr<GameObject> m_GameObject{};
	};
}

