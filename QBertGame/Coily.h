#pragma once
#include <memory>
#include "BaseComponent.h"


class QBert;

class Coily final : public dae::BaseComponent
{
public:
	explicit Coily(const std::shared_ptr<dae::GameObject>& gameObject, std::vector<QBert*>* qBertCompVector, int gameMode, int nrRows,
		float spriteWidth, float spriteHeight, int startingCube, float jumpInterval);
	~Coily() override = default;

	Coily(const Coily& other) = delete;
	Coily(Coily&& other) = delete;
	Coily& operator=(const Coily& other) = delete;
	Coily& operator=(Coily&& other) = delete;

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

	void QBertHit();

	bool CoilySeekBehaviour();
	bool ChaseQBert(int qBertRow, int qBertNrInRow, int coilyNrInRow, bool isPlayerOne);
	int CalculateQBertDistance(int qBertRow, int qBertNrInRow, int coilyNrInRow) const;
	bool FallIntoSpawnPos(float deltaTime);

	void Initialize() override;
	void Update(const float deltaTime) override;

private:
	enum class CoilyState
	{
		ST_FallingIntoSpawn,
		ST_EggJumping,
		ST_EggWaiting,
		ST_Transforming,
		ST_SnakeJumping,
		ST_SnakeWaiting,
		ST_InP2Control
	};
	
	std::shared_ptr<dae::GameObject> m_GameObject{};
	std::vector<QBert*>* m_QBertCompVector;

	bool m_Alive;
	bool m_Airborne;
	bool m_Frozen;
	
	int m_CurrentCubeIdx;
	int m_CurrentRow;
	int m_LastRow;
	
	float m_SpriteWidth, m_SpriteHeight;
	
	float m_JumpTimer;
	const float m_JumpInterval;
	float m_TransformTimer;
	const float m_TransformationTime;
	
	int m_Direction; // 1 is left/down, 2 is right/down, 3 is left/up and 4 is right/up
	int m_GameMode; // 1 is solo, 2 is Co-op, 3 is Versus
	CoilyState m_CurrentState;

	const float m_FallTime, m_FallHeight;
	float m_FallTimer, m_FinalLandingPosY, m_TimeSinceLastFrame;
	const int m_FPS;
};

