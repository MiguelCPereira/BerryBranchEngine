#include "MiniginPCH.h"
#include "QBertComponent.h"


// This class isn't the one I use in the game for QBert
// This is just here for the sake of the Engine Demo
// (the assignments we did throughout the semester)


dae::QBertComponent::QBertComponent(const std::shared_ptr<GameObject>& gameObject)
	: m_GameObject(gameObject)
{}

void dae::QBertComponent::ChangeTile() const
{
	// Play animation and sounds
	m_Subject->Notify(Event::TileChange);
}

void dae::QBertComponent::ChangeColor() const
{
	// Play animation and sounds
	m_Subject->Notify(Event::ColorChange);
}

void dae::QBertComponent::Die()
{
	if (m_Lives - 1 >= 0)
	{
		m_Lives--;
		// Play animation and sounds
		m_Subject->Notify(Event::ActorDeath);
	}
	else
	{
		// Game over
	}
}

void dae::QBertComponent::Update(const float)
{
	//if (changedColor)
	//	m_Subject->Notify(Event::ColorChange);
	
	//if (bumpedIntoCoily)
	//	Die();
}
