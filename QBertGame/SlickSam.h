#pragma once
#include <memory>
#include "BaseComponent.h"

class SlickSam final : public dae::BaseComponent
{
public:
	explicit SlickSam(const std::shared_ptr<dae::GameObject>& gameObject, int nrRows, float cubesWidth, float cubesHeight,
		float spriteWidth, float spriteHeight, int startingCube, float jumpInterval, bool isSlick);

	int GetPositionIndex() const { return m_CurrentCubeIdx; }

	void ChangeTile() const;
	void Die();

	bool GetIsAlive() const { return m_Alive; }

	bool MoveDown();
	bool MoveRight();

	void Update(const float deltaTime) override;

private:
	std::shared_ptr<dae::GameObject> m_GameObject{};
	int m_CurrentCubeIdx;
	int m_CurrentRow{ 2 };
	int m_LastRow;
	float m_CubesWidth, m_CubesHeight;
	float m_SpriteWidth, m_SpriteHeight;
	float m_JumpTimer{ 0 };
	const float m_JumpInterval;
	bool m_Alive{ true };
	bool m_IsSlick;
};

