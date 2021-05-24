#pragma once
#include <memory>
#include "BaseComponent.h"

namespace dae
{
	class Observer;
	class QBert final : public BaseComponent
	{
	public:
		explicit QBert(const std::shared_ptr<GameObject>& gameObject, const std::shared_ptr<GameObject>& cursesGameObject,
			int nrRows, float cubesWidth, float cubesHeight, float qBertSpriteWidth, float qBertSpriteHeight);

		int GetCurrentLives() const { return m_Lives; }
		int GetPositionIndex() const { return m_CurrentCubeIdx; }
		
		void Die();
		void ResetPosition();
		void SetFrozen(bool frozen);
		void SetHideGraphics(bool isHidden);
		void SetCursesHidden(bool isHidden) const;

		bool MoveUpRight();
		bool MoveUpLeft();
		bool MoveDownLeft();
		bool MoveDownRight();

		void Initialize() override;
		void Update(const float deltaTime) override;

	private:
		int m_Lives{ 3 };
		int m_HP{ 100 };
		bool m_Frozen{ true };
		std::shared_ptr<GameObject> m_GameObject{};
		std::shared_ptr<GameObject> m_CursesGameObject{};
		int m_CurrentCubeIdx{ 1 };
		int m_CurrentRow{ 1 };
		int m_LastRow;
		float m_CubesWidth, m_CubesHeight;
		float m_QBertSpriteWidth, m_QBertSpriteHeight;
		float m_QBertInitialPosX, m_QBertInitialPosY;
		float m_PosXBeforeHidden, m_PosYBeforeHidden;
		
	};
}


