#pragma once
#include <memory>
#include "BaseComponent.h"
#include "Observer.h"


class QBert;
class Coily;
class SlickSam;
class UggWrongway;

namespace dae
{
	class GraphicsComponent;
}

class JumpingObserver final : public dae::BaseComponent, public dae::Observer
{
public:
	explicit JumpingObserver(QBert* qBertComp, dae::GraphicsComponent* graphicsComp, float cubesWidth, float cubesHeight);
	explicit JumpingObserver(Coily* coilyComp, dae::GraphicsComponent* graphicsComp, float cubesWidth, float cubesHeight);
	explicit JumpingObserver(SlickSam* slickSamComp, dae::GraphicsComponent* graphicsComp, float cubesWidth, float cubesHeight);
	explicit JumpingObserver(UggWrongway* uggWrongComp, dae::GraphicsComponent* graphicsComp, float cubesWidth, float cubesHeight);
	~JumpingObserver() override;

	void SetQBert(QBert* qBertComp);
	void SetCoily(Coily* coilyComp);
	void SetSlickSam(SlickSam* slickSamComp);
	void SetUggWrongway(UggWrongway* uggWrongComp);
	void SetGraphics(dae::GraphicsComponent* graphicsComp);

	void Initialize() override;
	void Update(const float deltaTime) override;
	void OnNotify(const dae::Event& event) override;

private:
	QBert* m_QBertComp{};
	Coily* m_CoilyComp{};
	SlickSam* m_SlickSamComp{};
	UggWrongway* m_UggWrongComp{};
	dae::GraphicsComponent* m_GraphicsComp{};
	const float m_CubesWidth, m_CubesHeight;

	bool m_Jumping;
	const float m_JumpingSpeed;
	float m_LiftoffPosX, m_LiftoffPosY;
	float m_LandingPosX, m_LandingPosY;
	float m_MidFlightPosX, m_MidFlightPosY;
	bool m_MovingRight, m_MovingDown;
	bool m_MovementXIncomplete, m_MovementYIncomplete;
};

