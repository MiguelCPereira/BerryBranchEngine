#pragma once
#include <memory>
#include "BaseComponent.h"


class QBert;

class Coily final : public dae::BaseComponent
{
public:
	explicit Coily(const std::shared_ptr<dae::GameObject>& gameObject, std::vector<QBert*>* qBertCompVector, int gameMode, int nrRows,
		float cubesWidth, float cubesHeight, float spriteWidth, float spriteHeight, int startingCube, float jumpInterval);

	int GetPositionIndex() const { return m_CurrentCubeIdx; }
	bool GetIsAlive() const { return m_Alive; }
	bool GetAirborne() const { return m_Airborne; }

	void SetFrozen(bool frozen);
	void Die() const;

	bool MoveDownLeft();
	bool MoveDownRight();
	bool MoveUpLeft();
	bool MoveUpRight();
	bool MoveDownLeftPlayer();
	bool MoveDownRightPlayer();
	bool MoveUpLeftPlayer();
	bool MoveUpRightPlayer();
	void JumpFinished();

	bool CoilySeekBehaviour();
	bool ChaseQBert(int qBertRow, int qBertNrInRow, int coilyNrInRow, bool isPlayerOne);
	int CalculateQBertDistance(int qBertRow, int qBertNrInRow, int coilyNrInRow) const;

	void Update(const float deltaTime) override;

private:
	enum class CoilyStates
	{
		ST_EggJumping,
		ST_EggWaiting,
		ST_Transforming,
		ST_SnakeJumping,
		ST_SnakeWaiting,
		ST_InP2Control
	};
	
	std::shared_ptr<dae::GameObject> m_GameObject{};
	std::vector<QBert*>* m_QBertCompVector;
	bool m_Airborne{ false };
	bool m_Frozen{ false };
	int m_CurrentCubeIdx;
	int m_CurrentRow{ 2 };
	int m_LastRow;
	float m_CubesWidth, m_CubesHeight;
	float m_SpriteWidth, m_SpriteHeight;
	float m_JumpTimer{ 0 };
	const float m_JumpInterval;
	bool m_Alive{ true };
	float m_TransformTimer{ 0.f };
	const float m_TransformationTime{ 0.9f } ;
	int m_Direction; // 1 is left/down, 2 is right/down, 3 is left/up and 4 is right/up
	int m_GameMode; // 1 is solo, 2 is Co-op, 3 is Versus

	CoilyStates m_CurrentState;
};

