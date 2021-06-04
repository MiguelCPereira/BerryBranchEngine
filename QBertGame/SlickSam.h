#pragma once
#include <memory>
#include "BaseComponent.h"

class SlickSam final : public dae::BaseComponent
{
public:
	explicit SlickSam(const std::shared_ptr<dae::GameObject>& gameObject, int nrRows, float spriteWidth, float spriteHeight,
		int startingCube, float jumpInterval, bool isSlick);
	~SlickSam() override = default;

	SlickSam(const SlickSam& other) = delete;
	SlickSam(SlickSam&& other) = delete;
	SlickSam& operator=(const SlickSam& other) = delete;
	SlickSam& operator=(SlickSam&& other) = delete;
	
	int GetPositionIndex() const { return m_CurrentCubeIdx; }
	bool GetIsAlive() const { return m_Alive; }
	bool GetAirborne() const { return m_Airborne; }

	void SetFrozen(bool frozen);
	void Die() const;

	bool MoveDownLeft();
	bool MoveDownRight();
	void JumpFinished();

	bool FallIntoSpawnPos(float deltaTime);

	void Initialize() override;
	void Update(const float deltaTime) override;

private:
	enum class SlickSamState
	{
		ST_FallingIntoSpawn,
		ST_Jumping,
		ST_Waiting
	};
	
	std::shared_ptr<dae::GameObject> m_GameObject{};

	bool m_Alive;
	bool m_Airborne;
	bool m_Frozen;
	
	int m_CurrentCubeIdx;
	int m_CurrentRow;
	int m_LastRow;
	
	float m_SpriteWidth, m_SpriteHeight;
	
	float m_JumpTimer;
	const float m_JumpInterval;
	
	bool m_IsSlick;
	SlickSamState m_CurrentState;

	const float m_FallTime, m_FallHeight;
	float m_FallTimer, m_FinalLandingPosY, m_TimeSinceLastFrame;
	const int m_FPS;
};

