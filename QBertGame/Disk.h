#pragma once
#include <memory>
#include "BaseComponent.h"

namespace dae
{
	class GraphicsComponent;
}

class QBert;

class Disk final : public dae::BaseComponent
{
public:
	explicit Disk(const std::shared_ptr<dae::GameObject>& gameObject, int rowIdx, bool isLeft, int colorIdx,
		float finalPosX, float finalPosY, float finalQbertPosY, float spriteWidth, float spriteHeight);
	~Disk() override;

	Disk(const Disk& other) = delete;
	Disk(Disk&& other) noexcept = delete;
	Disk& operator=(const Disk& other) = delete;
	Disk& operator=(Disk&& other) noexcept = delete;

	void Activate(QBert* qBertComp, dae::GraphicsComponent* qBertGraphics, bool playerOne);
	void SetHide(bool isHidden);
	void SetFrozen(bool isFrozen);
	void ResetDisk();

	int GetRow() const { return m_RowIdx; }
	bool GetHasBeenUsed() const { return m_HasBeenUsed; }
	bool GetActivated() const { return m_Activated; }
	bool GetIsLeft() const { return m_IsLeft; }

	void Update(const float deltaTime) override;

private:
	std::shared_ptr<dae::GameObject> m_GameObject{};
	QBert* m_QBertComp;
	dae::GraphicsComponent* m_QBertGraphics;
	const int m_RowIdx;
	const bool m_IsLeft;
	const int m_ColorIdx;
	bool m_Activated;
	bool m_Frozen;

	const float m_FlightTime;
	const float m_QBertFallSpeed;
	const float m_InitialPosX, m_InitialPosY;
	const float m_FinalPosX, m_FinalPosY, m_FinalQBertPosY;
	float m_MidFlightPosX, m_MidFlightPosY;
	float m_QBertGraphAdjustmentX, m_QBertGraphAdjustmentY;
	bool m_FinalPositionReached;
	bool m_HasBeenUsed;

	bool m_Hidden;
	float m_PosBeforeHiddenX, m_PosBeforeHiddenY;

	const int m_FPSIdle, m_FPSFlight;
	float m_MidFlightTime;
	float m_TimeSinceLastFrameFlight;
	float m_TimeSinceLastFrameIdle;
	int m_CurrentFrame, m_NrFrames;
	const float m_SpriteWidth, m_SpriteHeight;

	bool m_CarryingPlayerOne;
};

