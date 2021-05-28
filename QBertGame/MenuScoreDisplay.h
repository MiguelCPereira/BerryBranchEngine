#pragma once
#include "BaseComponent.h"

class QBert;

class MenuScoreDisplay : public dae::BaseComponent
{
public:
	explicit MenuScoreDisplay(QBert* qBertComp, dae::TextComponent* textComp);
	~MenuScoreDisplay() override = default;

	void Initialize() override;
	void Update(const float deltaTime) override;

private:
	QBert* m_QBertComp;
	dae::TextComponent* m_TextComp;
};

