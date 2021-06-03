#pragma once
#include <memory>
#include "BaseComponent.h"

class UggWrongway final : public dae::BaseComponent
{
public:
	explicit UggWrongway(const std::shared_ptr<dae::GameObject>& gameObject, int nrRows, float cubesWidth, float cubesHeight,
		float spriteWidth, float spriteHeight, int startingCube, float jumpInterval, bool isUgg, bool startingLeft);

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

	void Update(const float deltaTime) override;

private:
	enum class UggWrongState
	{
		ST_Jumping,
		ST_Waiting
	};
	
	std::shared_ptr<dae::GameObject> m_GameObject{};
	bool m_Airborne{ false };
	bool m_Frozen{ false };
	int m_CurrentCubeIdx;
	int m_CurrentRow;
	int m_LastRow;
	float m_CubesWidth, m_CubesHeight;
	float m_SpriteWidth, m_SpriteHeight;
	float m_JumpTimer{ 0 };
	const float m_JumpInterval;
	bool m_Alive{ true };
	bool m_IsUgg, m_StartingLeft;

	UggWrongState m_CurrentState;
};

