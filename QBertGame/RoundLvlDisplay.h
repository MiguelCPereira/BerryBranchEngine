#pragma once
#include "BaseComponent.h"
#include "Observer.h"

class QBert;

class RoundLvlDisplay : public dae::BaseComponent, public dae::Observer
{
public:
	explicit RoundLvlDisplay(QBert* qBertComp, bool isCoOp, dae::TextComponent* levelTextComp, dae::TextComponent* roundTextComp);
	~RoundLvlDisplay() override;

	void SetQBert(QBert* qBertComp);

	void Initialize() override;
	void Update(const float deltaTime) override;
	void OnNotify(const dae::Event& event) override;

	void UpdateLevelText() const;
	void UpdateRoundText() const;

private:
	QBert* m_QBertComp;
	dae::TextComponent* m_LevelTextComp;
	dae::TextComponent* m_RoundTextComp;
	const bool m_IsCoOp;
};

