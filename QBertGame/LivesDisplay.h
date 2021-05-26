#pragma once
#include <vector>
#include "BaseComponent.h"
#include "Observer.h"

class QBert;

namespace dae
{
	class GraphicsComponent;
}

class LivesDisplay final : public dae::BaseComponent, public dae::Observer
{
public:
	explicit LivesDisplay(QBert* qBertComp);
	~LivesDisplay() override;

	void SetQBert(QBert* qBertComp);
	
	void Initialize() override;
	void Update(const float deltaTime) override;
	void OnNotify(const dae::Event& event) override;

private:
	QBert* m_QBertComp;
	std::vector<dae::GraphicsComponent*>* m_Graphics;
};

