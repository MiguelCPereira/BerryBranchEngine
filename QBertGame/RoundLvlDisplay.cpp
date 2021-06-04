#include "RoundLvlDisplay.h"
#include <string>
#include "TextComponent.h"

RoundLvlDisplay::RoundLvlDisplay(dae::TextComponent* levelTextComp, dae::TextComponent* roundTextComp, int level, int round)
	: m_LevelTextComp(levelTextComp)
	, m_RoundTextComp(roundTextComp)
	, m_Level(level)
	, m_Round(round)
{
}

RoundLvlDisplay::~RoundLvlDisplay()
{
	m_LevelTextComp = nullptr;
	m_RoundTextComp = nullptr;
}

void RoundLvlDisplay::Initialize()
{
	UpdateLevelText();
	UpdateRoundText();
}

void RoundLvlDisplay::Update(const float)
{
}

void RoundLvlDisplay::UpdateLevelText() const
{
	std::string string = "LEVEL: ";
	string.append(std::to_string(m_Level));
	m_LevelTextComp->SetText(string);
}

void RoundLvlDisplay::UpdateRoundText() const
{
	std::string string = "ROUND: ";
	string.append(std::to_string(m_Round));
	m_RoundTextComp->SetText(string);
}






