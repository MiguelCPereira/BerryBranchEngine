#pragma once
#include <memory>
#include "BaseComponent.h"

namespace dae
{
	class Observer;
	class QBert final : public BaseComponent
	{
	public:
		explicit QBert(const std::shared_ptr<GameObject>& gameObject, int nrRows, float cubesWidth, float cubesHeight,
			float qBertSpriteWidth, float qBertSpriteHeight);

		int GetCurrentLives() const { return m_Lives; }
		int GetPositionIndex() const { return m_CurrentCubeIdx; }
		
		void Die();
		void ResetPosition();
		void SetFrozen(bool frozen);
		void HideGraphics() const;

		bool MoveUpRight();
		bool MoveUpLeft();
		bool MoveDownLeft();
		bool MoveDownRight();

		void Initialize() override;
		void Update(const float deltaTime) override;

	private:
		int m_Lives{ 3 };
		int m_HP{ 100 };
		bool m_Frozen{ false };
		std::shared_ptr<GameObject> m_GameObject{};
		int m_CurrentCubeIdx{ 1 };
		int m_CurrentRow{ 1 };
		int m_LastRow;
		float m_CubesWidth, m_CubesHeight;
		float m_QBertSpriteWidth, m_QBertSpriteHeight;
		float m_QBertInitialPosX, m_QBertInitialPosY;
	};
}


