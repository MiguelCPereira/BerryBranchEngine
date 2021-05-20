#pragma once
#include <memory>
#include "BaseComponent.h"

namespace dae
{
	class Observer;
	class QBert final : public BaseComponent
	{
	public:
		explicit QBert(const std::shared_ptr<GameObject>& gameObject, int nrRows, float cubesWidth, float cubesHeight);

		int GetCurrentLives() const { return m_Lives; }
		void ChangeTile() const;
		void ChangeColor() const;
		void Die();

		bool MoveUp();
		bool MoveDown();
		bool MoveLeft();
		bool MoveRight();

		void Update(const float deltaTime) override;

	private:
		int m_Lives{ 3 };
		int m_HP{ 100 };
		std::shared_ptr<GameObject> m_GameObject{};
		int m_CurrentCubeIdx{ 1 };
		int m_CurrentRow{ 1 };
		int m_LastRow;
		float m_CubesWidth;
		float m_CubesHeight;
	};
}


