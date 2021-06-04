#pragma once
#include <memory>
#include "BaseComponent.h"

class UggWrongway final : public dae::BaseComponent
{
public:
	explicit UggWrongway(const std::shared_ptr<dae::GameObject>& gameObject, int nrRows, float spriteWidth, float spriteHeight,
		int startingCube, float jumpInterval, bool isUgg, bool startingLeft);
	~UggWrongway() override = default;
	
	UggWrongway(const UggWrongway& other) = delete;
	UggWrongway(UggWrongway&& other) = delete;
	UggWrongway& operator=(const UggWrongway& other) = delete;
	UggWrongway& operator=(UggWrongway&& other) = delete;
	
	int GetPositionIndex() const { return m_CurrentCubeIdx; }
	bool GetIsAlive() const { return m_Alive; }
	bool GetStartedLeft() const { return m_StartingLeft; }
	int GetCurrentRow() const { return m_CurrentRow; }
	bool GetAirborne() const { return m_Airborne; }

	void SetFrozen(bool frozen);
	void Die() const;

	// If the name of the movement functions seem confusing
	// Picture if the sprite was drawn on top of the cube,
	// just like the other characters, instead of on the side
	bool MoveUpLeft();
	bool MoveUpRight();
	bool MoveLeft();
	bool MoveRight();
	void JumpFinished();

	bool FallIntoSpawnPos(float deltaTime);
	
	void Initialize() override;
	void Update(const float deltaTime) override;

private:
	enum class UggWrongState
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

	float m_SpriteWidth, m_SpriteHeight;
	
	float m_JumpTimer;
	const float m_JumpInterval;
	
	bool m_IsUgg, m_StartingLeft;
	UggWrongState m_CurrentState;

	const float m_FallTime, m_FallHeightWidth;
	float m_FallTimer, m_FinalLandingPosX, m_FinalLandingPosY, m_TimeSinceLastFrame;
	const int m_FPS;
};

