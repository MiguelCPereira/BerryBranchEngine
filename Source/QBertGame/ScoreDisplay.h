#pragma once
#include "BaseComponent.h"
#include "Observer.h"

class QBert;

class ScoreDisplay : public dae::BaseComponent, public dae::Observer
{
public:
	explicit ScoreDisplay(QBert* qBertComp, dae::TextComponent* textComp);
	~ScoreDisplay() override;

	ScoreDisplay(const ScoreDisplay& other) = delete;
	ScoreDisplay(ScoreDisplay&& other) noexcept = delete;
	ScoreDisplay& operator=(const ScoreDisplay& other) = delete;
	ScoreDisplay& operator=(ScoreDisplay&& other) noexcept = delete;

	void SetQBert(QBert* qBertComp);

	void Initialize() override;
	void Update(const float deltaTime) override;
	void OnNotify(const dae::Event& event) override;

	void UpdateScoreText() const;

private:
	QBert* m_QBertComp;
	dae::TextComponent* m_TextComp;
};
