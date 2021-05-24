#pragma once
#include <memory>
#include "BaseComponent.h"
#include "Observer.h"


class QBert;

namespace dae
{
	class GraphicsComponent;
}

class JumpingObserver final : public dae::BaseComponent, public dae::Observer
{
public:
	explicit JumpingObserver(const std::shared_ptr<dae::GameObject>& gameObject, QBert* qBertComp,
		dae::GraphicsComponent* graphicsComp, float cubesWidth, float cubesHeight);
	~JumpingObserver() override;

	void SetQBert(QBert* qBertComp);
	void SetGraphics(dae::GraphicsComponent* graphicsComp);

	void Initialize() override;
	void Update(const float deltaTime) override;
	void OnNotify(const dae::Event& event) override;

private:
	std::shared_ptr<dae::GameObject> m_GameObject{};
	QBert* m_QBertComp{};
	dae::GraphicsComponent* m_GraphicsComp{};
	const float m_CubesWidth, m_CubesHeight;
};

