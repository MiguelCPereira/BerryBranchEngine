#include "ScoreDisplay.h"
#include <string>
#include "Factory.h"
#include "GameObject.h"
#include "QBert.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "TextComponent.h"


ScoreDisplay::ScoreDisplay(QBert* qBertComp, dae::TextComponent* textComp)
	: m_QBertComp(qBertComp)
	, m_TextComp(textComp)
{
}

ScoreDisplay::~ScoreDisplay()
{
	if (m_QBertComp != nullptr)
		m_QBertComp->GetSubject()->RemoveObserver(this);

	m_TextComp = nullptr;
}


void ScoreDisplay::Initialize()
{
	if (m_QBertComp != nullptr)
	{
		m_QBertComp->GetSubject()->AddObserver(this);
		UpdateScoreText();
	}
}


void ScoreDisplay::SetQBert(QBert* qBertComp)
{
	if (m_QBertComp != nullptr)
		m_QBertComp->GetSubject()->RemoveObserver(this);

	m_QBertComp = qBertComp;

	if (m_QBertComp != nullptr)
		m_QBertComp->GetSubject()->AddObserver(this);
}


void ScoreDisplay::OnNotify(const dae::Event& event)
{
	switch (event)
	{
	case dae::Event::ScoreIncreasedP1:
		UpdateScoreText();
		break;
	case dae::Event::ScoreIncreasedP2:
		UpdateScoreText();
		break;
	}
}

void ScoreDisplay::Update(const float)
{
}

void ScoreDisplay::UpdateScoreText() const
{
	std::string string = "SCORE: ";
	string.append(std::to_string(m_QBertComp->GetScore()));
	m_TextComp->SetText(string);
}