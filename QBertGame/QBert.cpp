#include "QBert.h"
#include <iostream>
#include "GameObject.h"
#include "GraphicsComponent.h"


dae::QBert::QBert(const std::shared_ptr<GameObject>& gameObject, int nrRows, float cubesWidth, float cubesHeight,
	float qBertSpriteWidth, float qBertSpriteHeight)
	: m_GameObject(gameObject)
	, m_LastRow(nrRows)
	, m_CubesWidth(cubesWidth)
	, m_CubesHeight(cubesHeight)
	, m_QBertSpriteWidth(qBertSpriteWidth)
	, m_QBertSpriteHeight(qBertSpriteHeight)
	, m_QBertInitialPosX()
	, m_QBertInitialPosY()
{}


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

void dae::QBert::ResetPosition()
{
	m_CurrentCubeIdx = 1;
	m_CurrentRow = 1;
	m_GameObject->GetComponent<GraphicsComponent>()->SetPosition(m_QBertInitialPosX, m_QBertInitialPosY);
	m_GameObject->GetComponent<GraphicsComponent>()->SetSrcRectangle(m_QBertSpriteWidth * 2, 0, m_QBertSpriteWidth, m_QBertSpriteHeight);

}

void dae::QBert::SetFrozen(bool frozen)
{
	m_Frozen = frozen;
}

void dae::QBert::HideGraphics() const
{
	m_GameObject->GetComponent<GraphicsComponent>()->SetPosition(-50, -50);
}

bool dae::QBert::MoveUpRight()
{
	if (m_Frozen == false)
	{
		// If QBert isn't in the end of any of the pyramid rows
		if (m_CurrentCubeIdx != m_CurrentRow * (m_CurrentRow + 1) / 2)
		{
			m_CurrentCubeIdx = m_CurrentCubeIdx - m_CurrentRow + 1;
			m_CurrentRow--;
			auto* graphics = m_GameObject->GetComponent<GraphicsComponent>();
			graphics->SetPosition(graphics->GetPosX() + m_CubesWidth / 2.f, graphics->GetPosY() - m_CubesHeight * 0.75f);
			graphics->SetSrcRectangle(0, 0, m_QBertSpriteWidth, m_QBertSpriteHeight);
			m_Subject->Notify(Event::QBertMove);
			return true;
		}
		return false;
	}
	return false;
}

bool dae::QBert::MoveUpLeft()
{
	if (m_Frozen == false)
	{
		// If QBert isn't in the beginning of any of the pyramid rows
		if (m_CurrentCubeIdx != m_CurrentRow * (m_CurrentRow + 1) / 2 - m_CurrentRow + 1 && m_CurrentCubeIdx != 1)
		{
			m_CurrentCubeIdx = m_CurrentCubeIdx - m_CurrentRow;
			m_CurrentRow--;
			auto* graphics = m_GameObject->GetComponent<GraphicsComponent>();
			graphics->SetPosition(graphics->GetPosX() - m_CubesWidth / 2.f, graphics->GetPosY() - m_CubesHeight * 0.75f);
			graphics->SetSrcRectangle(m_QBertSpriteWidth, 0, m_QBertSpriteWidth, m_QBertSpriteHeight);
			m_Subject->Notify(Event::QBertMove);
			return true;
		}
		return false;
	}
	return false;
}

bool dae::QBert::MoveDownLeft()
{
	if (m_Frozen == false)
	{
		// If QBert isn't in the last pyramid row
		if (m_CurrentRow != m_LastRow)
		{
			m_CurrentCubeIdx = m_CurrentCubeIdx + m_CurrentRow;
			m_CurrentRow++;
			auto* graphics = m_GameObject->GetComponent<GraphicsComponent>();
			graphics->SetPosition(graphics->GetPosX() - m_CubesWidth / 2.f, graphics->GetPosY() + m_CubesHeight * 0.75f);
			graphics->SetSrcRectangle(m_QBertSpriteWidth * 3, 0, m_QBertSpriteWidth, m_QBertSpriteHeight);
			m_Subject->Notify(Event::QBertMove);
			return true;
		}
		return false;
	}
	return false;
}

bool dae::QBert::MoveDownRight()
{
	if (m_Frozen == false)
	{
		// If QBert isn't in the last pyramid row
		if (m_CurrentRow != m_LastRow)
		{
			m_CurrentCubeIdx = m_CurrentCubeIdx + m_CurrentRow + 1;
			m_CurrentRow++;
			auto* graphics = m_GameObject->GetComponent<GraphicsComponent>();
			graphics->SetPosition(graphics->GetPosX() + m_CubesWidth / 2.f, graphics->GetPosY() + m_CubesHeight * 0.75f);
			graphics->SetSrcRectangle(m_QBertSpriteWidth * 2, 0, m_QBertSpriteWidth, m_QBertSpriteHeight);
			m_Subject->Notify(Event::QBertMove);
			return true;
		}
		return false;
	}
	return false;
}


void dae::QBert::Initialize()
{
	auto* graphics = m_GameObject->GetComponent<GraphicsComponent>();
	m_QBertInitialPosX = graphics->GetPosX();
	m_QBertInitialPosY = graphics->GetPosY();
}

void dae::QBert::Update(const float)
{
	//if (changedColor)
	//	m_Subject->Notify(Event::ColorChange);

	//if (bumpedIntoCoily)
	//	Die();
}

