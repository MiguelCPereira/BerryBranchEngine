#include "MiniginPCH.h"
#include "PointsDisplayComponent.h"
#include "QBertComponent.h"
#include "TextComponent.h"
#include "GameObject.h"


// This class isn't the one I use in the game for the score display
// This is just here for the sake of the Engine Demo
// (the assignments we did throughout the semester)


dae::PointsDisplayComponent::PointsDisplayComponent(const std::shared_ptr<GameObject>& gameObject, QBertComponent* qBertComp)
	: m_QBertComp(qBertComp),
	m_GameObject(gameObject),
	m_TileChangeIncrement(25),
	m_ColorChangeIncrement(10)
{}

dae::PointsDisplayComponent::~PointsDisplayComponent()
{
	if (m_QBertComp != nullptr)
		m_QBertComp->GetSubject()->RemoveObserver(this);

	delete m_TextComp;
	m_TextComp = nullptr;
}

void dae::PointsDisplayComponent::Initialize()
{
	m_TextComp = m_GameObject->GetComponent<TextComponent>();

	if (m_QBertComp != nullptr)
	{
		m_QBertComp->GetSubject()->AddObserver(this);
		std::string string = "Points: ";
		string.append(std::to_string(m_Score));
		m_TextComp->SetText(string);
	}
}

void dae::PointsDisplayComponent::SetQBert(QBertComponent* qBertComp)
{
	if (m_QBertComp != nullptr)
		m_QBertComp->GetSubject()->RemoveObserver(this);

	m_QBertComp = qBertComp;

	if (m_QBertComp != nullptr)
	{
		m_QBertComp->GetSubject()->AddObserver(this);
		std::string string = "Points: ";
		string.append(std::to_string(m_Score));
		m_TextComp->SetText(string);
	}
}

void dae::PointsDisplayComponent::OnNotify(const Event& event)
{
	std::string string;
	
	switch (event)
	{
	case Event::TileChange:
		m_Score += m_TileChangeIncrement;
		string = "Points: ";
		string.append(std::to_string(m_Score));
		m_TextComp->SetText(string);
		break;
	case Event::ColorChange:
		m_Score += m_ColorChangeIncrement;
		string = "Points: ";
		string.append(std::to_string(m_Score));
		m_TextComp->SetText(string);
		break;
	}
}
