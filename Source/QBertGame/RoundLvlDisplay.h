#pragma once
#include "BaseComponent.h"

class RoundLvlDisplay : public dae::BaseComponent
{
public:
	explicit RoundLvlDisplay(dae::TextComponent* levelTextComp, dae::TextComponent* roundTextComp, int level, int round);
	~RoundLvlDisplay() override;

	RoundLvlDisplay(const RoundLvlDisplay& other) = delete;
	RoundLvlDisplay(RoundLvlDisplay&& other) noexcept = delete;
	RoundLvlDisplay& operator=(const RoundLvlDisplay& other) = delete;
	RoundLvlDisplay& operator=(RoundLvlDisplay&& other) noexcept = delete;

	void Initialize() override;
	void Update(const float deltaTime) override;

	void UpdateLevelText() const;
	void UpdateRoundText() const;

private:
	dae::TextComponent* m_LevelTextComp;
	dae::TextComponent* m_RoundTextComp;
	const int m_Level, m_Round;
};

