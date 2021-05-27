#pragma once
#include <memory>
#include "BaseComponent.h"


class QBert;

class Coily final : public dae::BaseComponent
{
public:
	explicit Coily(const std::shared_ptr<dae::GameObject>& gameObject, QBert* qBertComp, int nrRows, float cubesWidth,
		float cubesHeight, float spriteWidth, float spriteHeight, int startingCube, float jumpInterval);

	int GetPositionIndex() const { return m_CurrentCubeIdx; }
	bool GetIsAlive() const { return m_Alive; }
	bool GetAirborne() const { return m_Airborne; }

	void SetFrozen(bool frozen);
	void Die() const;

	bool MoveDownLeft();
	bool MoveDownRight();
	bool MoveUpLeft();
	bool MoveUpRight();
	void JumpFinished();

	void Update(const float deltaTime) override;

private:
	std::shared_ptr<dae::GameObject> m_GameObject{};
	QBert* m_QBertComp;
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
	bool m_IsEgg{ true };
	bool m_IsTransforming{ false };
	float m_TransformTimer{ 0.f };
	const float m_TransformationTime{ 0.9f } ;
	int m_Direction; // 1 is left/down, 2 is right/down, 3 is left/up and 4 is right/up
};

