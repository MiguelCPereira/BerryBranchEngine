#include "MenuScoreDisplay.h"

#include <string>

#include "QBert.h"
#include "TextComponent.h"

MenuScoreDisplay::MenuScoreDisplay(QBert* qBertComp, dae::TextComponent* textComp)
	: m_QBertComp(qBertComp)
	, m_TextComp(textComp)
{
}

void MenuScoreDisplay::Initialize()
{
	const auto score = m_QBertComp->GetScore();

	int nrOfDigits = 0;
	int temp = score;
	while (temp != 0)
	{
		temp /= 10;
		nrOfDigits++;
	}

	switch (nrOfDigits)
	{
	case 0:
		m_TextComp->SetText("00000" + std::to_string(score));
		break;
	case 1:
		m_TextComp->SetText("00000" + std::to_string(score));
		break;
	case 2:
		m_TextComp->SetText("0000" + std::to_string(score));
		break;
	case 3:
		m_TextComp->SetText("000" + std::to_string(score));
		break;
	case 4:
		m_TextComp->SetText("00" + std::to_string(score));
		break;
	case 5:
		m_TextComp->SetText("0" + std::to_string(score));
		break;
	default:
		m_TextComp->SetText(std::to_string(score));
		break;
	}
}

void MenuScoreDisplay::Update(const float)
{
}



