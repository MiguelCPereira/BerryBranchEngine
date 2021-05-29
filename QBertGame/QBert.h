#pragma once
#include <memory>
#include "BaseComponent.h"

namespace dae
{
	class Observer;
}

class QBert final : public dae::BaseComponent
{
public:
	explicit QBert(const std::shared_ptr<dae::GameObject>& gameObject, const std::shared_ptr<dae::GameObject>& cursesGameObject,
		int nrRows, float qBertSpriteWidth, float qBertSpriteHeight);

	int GetCurrentLives() const { return m_Lives; }
	int GetPositionIndex() const { return m_CurrentCubeIdx; }
	int GetCurrentRow() const { return m_CurrentRow; }
	bool GetAirborne() const { return m_Airborne; }
	int GetMaxLives() const { return m_MaxLives; }
	int GetScore() const { return m_Score; }
	bool GetJumpedOff() const { return m_JumpedOff;  }
	bool GetLastJumpedOffLeft() const { return m_LastJumpedOffLeft; }
	int GetLevel() const { return m_Level; }
	int GetRound() const { return m_Round; }
		
	void Die();
	void ResetGameVariables();
	void ResetPosition();
	void RevertToLastPosition();
	void SetFrozen(bool frozen);
	void SetHideGraphics(bool isHidden);
	void SetCursesHidden(bool isHidden) const;
	void BackToGround();

	void SetNewPositionIndexes(int cubeIdx, int rowNr);
	void ScoreIncrease(int gainedPoints);
	void SetLevel(int actualLevel);
	void SetRound(int actualRound);

	bool IsInLeftBorder() const;
	bool IsInRightBorder() const;
	bool MoveUpRight();
	bool MoveUpLeft();
	bool MoveDownLeft();
	bool MoveDownRight();
	void JumpFinished();

	void Initialize() override;
	void Update(const float deltaTime) override;

private:
	const int m_MaxLives{ 3 };
	int m_Lives{ 3 };
	int m_Score{ 0 };
	
	bool m_Airborne{ false };
	bool m_Frozen{ true };
	
	std::shared_ptr<dae::GameObject> m_GameObject{};
	std::shared_ptr<dae::GameObject> m_CursesGameObject{};
	
	int m_CurrentCubeIdx{ 1 };
	int m_CurrentRow{ 1 };
	int m_LastRow;

	bool m_JumpedOff{ false };
	bool m_LastJumpedOffLeft{};
	float m_PosXBeforeFalling{};
	float m_PosYBeforeFalling{};
	
	float m_QBertSpriteWidth, m_QBertSpriteHeight;
	float m_QBertInitialPosX, m_QBertInitialPosY;
	float m_PosXBeforeHidden, m_PosYBeforeHidden;
	
	int m_Level{ 0 };
	int m_Round{ 1 };
};


