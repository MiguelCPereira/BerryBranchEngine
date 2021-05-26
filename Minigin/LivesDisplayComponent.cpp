#include "MiniginPCH.h"
#include "LivesDisplayComponent.h"
#include "QBertComponent.h"
#include "TextComponent.h"
#include "GameObject.h"


// This class isn't the one I use in the game for the lives display
// This is just here for the sake of the Engine Demo
// (the assignments we did throughout the semester)


dae::LivesDisplayComponent::LivesDisplayComponent(const std::shared_ptr<GameObject>& gameObject, QBertComponent* qBertComp)
	: m_QBertComp(qBertComp),
	m_GameObject(gameObject)
{}

dae::LivesDisplayComponent::~LivesDisplayComponent()
{
	if (m_QBertComp != nullptr)
		m_QBertComp->GetSubject()->RemoveObserver(this);

	delete m_TextComp;
	m_TextComp = nullptr;
}

void dae::LivesDisplayComponent::Initialize()
{
	m_TextComp = m_GameObject->GetComponent<TextComponent>();
	
	if (m_QBertComp != nullptr)
	{
		m_QBertComp->GetSubject()->AddObserver(this);
		std::string string = "Remaining Lives: ";
		string.append(std::to_string(m_QBertComp->GetCurrentLives()));
		m_TextComp->SetText(string);
	}
}

void dae::LivesDisplayComponent::SetQBert(QBertComponent* qBertComp)
{
	if (m_QBertComp != nullptr)
		m_QBertComp->GetSubject()->RemoveObserver(this);

	m_QBertComp = qBertComp;
	
	if (m_QBertComp != nullptr)
	{
		m_QBertComp->GetSubject()->AddObserver(this);
		std::string string = "Remaining Lives: ";
		string.append(std::to_string(m_QBertComp->GetCurrentLives()));
		m_TextComp->SetText(string);
	}
}

void dae::LivesDisplayComponent::OnNotify(const Event& event)
{
	switch (event)
	{
	case Event::ActorDeath:
		std::string string = "Remaining Lives: ";
		string.append(std::to_string(m_QBertComp->GetCurrentLives()));
		m_TextComp->SetText(string);
		break;
	}
}