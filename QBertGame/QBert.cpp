#include "QBert.h"


dae::QBert::QBert(const std::shared_ptr<GameObject>& gameObject)
	: m_GameObject(gameObject)
{}

void dae::QBert::ChangeTile() const
{
	// Play animation and sounds
	m_Subject->Notify(Event::TileChange);
}

void dae::QBert::ChangeColor() const
{
	// Play animation and sounds
	m_Subject->Notify(Event::ColorChange);
}

void dae::QBert::Die()
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

void dae::QBert::Update(const float)
{
	//if (changedColor)
	//	m_Subject->Notify(Event::ColorChange);

	//if (bumpedIntoCoily)
	//	Die();
}

