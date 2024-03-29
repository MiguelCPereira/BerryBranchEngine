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
		int nrRows, float qBertSpriteWidth, float qBertSpriteHeight, bool isPlayerOne);
	~QBert() override = default;

	QBert(const QBert& other) = delete;
	QBert(QBert&& other) = delete;
	QBert& operator=(const QBert& other) = delete;
	QBert& operator=(QBert&& other) = delete;

	int GetCurrentLives() const { return m_Lives; }
	int GetPositionIndex() const { return m_CurrentCubeIdx; }
	int GetCurrentRow() const { return m_CurrentRow; }
	bool GetAirborne() const { return m_Airborne; }
	int GetMaxLives() const { return m_MaxLives; }
	int GetScore() const { return m_Score; }
	bool GetJumpedOff() const { return m_JumpedOff;  }
	bool GetLastJumpedOffLeft() const { return m_LastJumpedOffLeft; }
	bool GetLastJumpedOffDown() const { return m_LastJumpedOffDown; }
	bool GetIsInDisk() const { return m_IsInDisk;  }

	bool AreGraphicsHidden() const;
	
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
	void SetIsInDisk(bool inDisk);

	bool IsInLeftBorder() const;
	bool IsInRightBorder() const;
	bool MoveUpRight();
	bool MoveUpLeft();
	bool MoveDownLeft();
	bool MoveDownRight();
	void JumpFinished();

	void PauseGame() const;
	void BackToMenu() const;
	void AnimationStopped() const;

	void Initialize() override;
	void Update(const float deltaTime) override;

private:
	const int m_MaxLives{ 3 };
	int m_Lives{ 3 };
	int m_Score{ 0 };
	
	bool m_Airborne{ false };
	bool m_Frozen{ true };
	bool m_IsInDisk{ false };
	
	std::shared_ptr<dae::GameObject> m_GameObject{};
	std::shared_ptr<dae::GameObject> m_CursesGameObject{};

	int m_JumpedToCubeIdx {1 };
	int m_JumpedToRowIdx{ 1 };
	
	int m_CurrentCubeIdx{ 1 };
	int m_CurrentRow{ 1 };
	int m_LastRow;

	bool m_JumpedOff{ false };
	bool m_LastJumpedOffLeft{};
	bool m_LastJumpedOffDown{};
	float m_PosXBeforeFalling{};
	float m_PosYBeforeFalling{};
	
	float m_QBertSpriteWidth, m_QBertSpriteHeight;
	float m_QBertInitialPosX, m_QBertInitialPosY;
	float m_PosXBeforeHidden, m_PosYBeforeHidden;

	bool m_IsPlayerOne;
};


