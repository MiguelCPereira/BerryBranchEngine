#include "RoundLvlDisplay.h"

#include <string>

#include "GameObject.h"
#include "Factory.h"
#include "QBert.h"
#include "SceneManager.h"
#include "Scene.h"
#include "TextComponent.h"

RoundLvlDisplay::RoundLvlDisplay(QBert* qBertComp, bool isCoOp)
	: m_QBertComp(qBertComp)
	, m_LevelTextComp()
	, m_RoundTextComp()
	, m_IsCoOp(isCoOp)
{
}

RoundLvlDisplay::~RoundLvlDisplay()
{
	if (m_QBertComp != nullptr)
		m_QBertComp->GetSubject()->RemoveObserver(this);

	m_LevelTextComp = nullptr;
	m_RoundTextComp = nullptr;
}

void RoundLvlDisplay::Initialize()
{
	if (m_QBertComp != nullptr)
	{
		m_QBertComp->GetSubject()->AddObserver(this);
		m_QBertComp->SetFrozen(false);
	}

	auto lvlDisplayGO = MakeLevelDisplay(m_IsCoOp);
	m_LevelTextComp = lvlDisplayGO->GetComponent<dae::TextComponent>();
	auto roundDisplayGO = MakeRoundDisplay(m_IsCoOp);
	m_RoundTextComp = roundDisplayGO->GetComponent<dae::TextComponent>();
	UpdateLevelText();
	UpdateRoundText();
	dae::SceneManager::GetInstance().GetCurrentScene()->Add(lvlDisplayGO);
	dae::SceneManager::GetInstance().GetCurrentScene()->Add(roundDisplayGO);
}

void RoundLvlDisplay::SetQBert(QBert* qBertComp)
{
	if (m_QBertComp != nullptr)
		m_QBertComp->GetSubject()->RemoveObserver(this);

	m_QBertComp = qBertComp;

	if (m_QBertComp != nullptr)
		m_QBertComp->GetSubject()->AddObserver(this);
}

void RoundLvlDisplay::OnNotify(const dae::Event& event)
{
	switch (event)
	{
	case dae::Event::LevelUpdated:
		UpdateLevelText();
		break;
	case dae::Event::RoundUpdated:
		UpdateRoundText();
		break;
	}
}

void RoundLvlDisplay::Update(const float)
{
}

void RoundLvlDisplay::UpdateLevelText() const
{
	std::string string = "LEVEL: ";
	string.append(std::to_string(m_QBertComp->GetLevel()));
	m_LevelTextComp->SetText(string);
}

void RoundLvlDisplay::UpdateRoundText() const
{
	std::string string = "ROUND: ";
	string.append(std::to_string(m_QBertComp->GetRound()));
	m_RoundTextComp->SetText(string);
}






