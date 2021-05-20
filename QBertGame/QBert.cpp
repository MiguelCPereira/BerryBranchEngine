#include "QBert.h"

#include "GameObject.h"
#include "GraphicsComponent.h"


dae::QBert::QBert(const std::shared_ptr<GameObject>& gameObject, int nrRows, float cubesWidth, float cubesHeight)
	: m_GameObject(gameObject)
	, m_LastRow(nrRows)
	, m_CubesWidth(cubesWidth)
	, m_CubesHeight(cubesHeight)
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

bool dae::QBert::MoveUp()
{
	// If QBert isn't in the end of any of the pyramid rows
	if (m_CurrentCubeIdx != m_CurrentRow * (m_CurrentRow + 1) / 2)
	{
		m_CurrentCubeIdx = m_CurrentCubeIdx - m_CurrentRow + 1;
		m_CurrentRow--;
		m_Subject->Notify(Event::QBertMoveUp);
		auto* graphics = m_GameObject->GetComponent<GraphicsComponent>();
		graphics->SetPosition(graphics->GetPosX() + m_CubesWidth / 2.f, graphics->GetPosY() - m_CubesHeight);
		return true;
	}
	
	return false;
}

bool dae::QBert::MoveDown()
{
	// If QBert isn't in the last pyramid row
	if (m_CurrentRow != m_LastRow)
	{
		m_CurrentCubeIdx = m_CurrentCubeIdx + m_CurrentRow;
		m_CurrentRow++;
		m_Subject->Notify(Event::QBertMoveDown);
		auto* graphics = m_GameObject->GetComponent<GraphicsComponent>();
		graphics->SetPosition(graphics->GetPosX() - m_CubesWidth / 2.f, graphics->GetPosY() + m_CubesHeight);
		return true;
	}

	return false;
}

bool dae::QBert::MoveLeft()
{
	// If QBert isn't in the beginning of any of the pyramid rows
	if (m_CurrentCubeIdx != m_CurrentRow * (m_CurrentRow + 1) / 2 + 1 && m_CurrentCubeIdx != 1)
	{
		m_CurrentCubeIdx = m_CurrentCubeIdx - m_CurrentRow;
		m_CurrentRow++;
		auto* graphics = m_GameObject->GetComponent<GraphicsComponent>();
		graphics->SetPosition(graphics->GetPosX() - m_CubesWidth / 2.f, graphics->GetPosY() - m_CubesHeight);
		return true;
	}

	return false;
}

bool dae::QBert::MoveRight()
{
	// If QBert isn't in the last pyramid row
	if (m_CurrentRow != m_LastRow)
	{
		m_CurrentCubeIdx = m_CurrentCubeIdx + m_CurrentRow + 1;
		m_CurrentRow++;
		auto* graphics = m_GameObject->GetComponent<GraphicsComponent>();
		graphics->SetPosition(graphics->GetPosX() + m_CubesWidth / 2.f, graphics->GetPosY() + m_CubesHeight);
		return true;
	}

	return false;
}


void dae::QBert::Update(const float)
{
	//if (changedColor)
	//	m_Subject->Notify(Event::ColorChange);

	//if (bumpedIntoCoily)
	//	Die();
}

