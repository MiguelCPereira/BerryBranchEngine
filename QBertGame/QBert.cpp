#include "QBert.h"
#include <iostream>
#include "GameObject.h"
#include "GraphicsComponent.h"


QBert::QBert(const std::shared_ptr<dae::GameObject>& gameObject, const std::shared_ptr<dae::GameObject>& cursesGameObject,
	int nrRows, float qBertSpriteWidth, float qBertSpriteHeight)
	: m_GameObject(gameObject)
	, m_CursesGameObject(cursesGameObject)
	, m_LastRow(nrRows)
	, m_QBertSpriteWidth(qBertSpriteWidth)
	, m_QBertSpriteHeight(qBertSpriteHeight)
	, m_QBertInitialPosX()
	, m_QBertInitialPosY()
	, m_PosXBeforeHidden()
	, m_PosYBeforeHidden()
{}


void QBert::Die()
{
	if (m_Lives - 1 >= 0)
	{
		m_Lives--;
		std::cout << "Ouch! You now have " << m_Lives << " lives left\n";
		// Play sound
		m_Subject->Notify(dae::Event::QBertDied);
	}
	else
	{
		std::cout << "You just lost your last life, game over\n";
		// Game over
	}
}

void QBert::ResetPosition()
{
	m_CurrentCubeIdx = 1;
	m_CurrentRow = 1;
	m_GameObject->GetComponent<dae::GraphicsComponent>()->SetPosition(m_QBertInitialPosX, m_QBertInitialPosY);
	m_GameObject->GetComponent<dae::GraphicsComponent>()->SetSrcRectangle(m_QBertSpriteWidth * 2, 0, m_QBertSpriteWidth, m_QBertSpriteHeight);

}

void QBert::SetFrozen(bool frozen)
{
	m_Frozen = frozen;
}

void QBert::SetHideGraphics(bool isHidden)
{
	if (isHidden)
	{
		m_PosXBeforeHidden = m_GameObject->GetComponent<dae::GraphicsComponent>()->GetPosX();
		m_PosYBeforeHidden = m_GameObject->GetComponent<dae::GraphicsComponent>()->GetPosY();
		m_GameObject->GetComponent<dae::GraphicsComponent>()->SetPosition(-50, -50);
	}
	else
	{
		m_GameObject->GetComponent<dae::GraphicsComponent>()->SetPosition(m_PosXBeforeHidden, m_PosYBeforeHidden);
	}
}

void QBert::SetCursesHidden(bool isHidden) const
{
	auto posX = -50.f;
	auto posY = -50.f;
	
	if (isHidden == false)
	{
		posX = m_GameObject->GetComponent<dae::GraphicsComponent>()->GetPosX() + 5.f;
		posY = m_GameObject->GetComponent<dae::GraphicsComponent>()->GetPosY() - 38.f;
	}

	m_CursesGameObject->GetComponent<dae::GraphicsComponent>()->SetPosition(posX, posY);
}

void QBert::ScoreIncrease(int gainedPoints)
{
	m_Score += gainedPoints;
	m_Subject->Notify(dae::Event::ScoreIncreased);
}

void QBert::SetLevel(int actualLevel)
{
	m_Level = actualLevel;
	m_Subject->Notify(dae::Event::LevelUpdated);
}

void QBert::SetRound(int actualRound)
{
	m_Round = actualRound;
	m_Subject->Notify(dae::Event::RoundUpdated);
}

bool QBert::MoveUpRight()
{
	if (m_Frozen == false && m_Airborne == false)
	{
		// If QBert isn't in the end of any of the pyramid rows
		if (m_CurrentCubeIdx != m_CurrentRow * (m_CurrentRow + 1) / 2)
		{
			m_CurrentCubeIdx = m_CurrentCubeIdx - m_CurrentRow + 1;
			m_CurrentRow--;
			auto* graphics = m_GameObject->GetComponent<dae::GraphicsComponent>();
			graphics->SetSrcRectangle(0, 0, m_QBertSpriteWidth, m_QBertSpriteHeight);
			m_Airborne = true;
			m_Subject->Notify(dae::Event::JumpUpRight);
			return true;
		}
		return false;
	}
	return false;
}

bool QBert::MoveUpLeft()
{
	if (m_Frozen == false && m_Airborne == false)
	{
		// If QBert isn't in the beginning of any of the pyramid rows
		if (m_CurrentCubeIdx != m_CurrentRow * (m_CurrentRow + 1) / 2 - m_CurrentRow + 1 && m_CurrentCubeIdx != 1)
		{
			m_CurrentCubeIdx = m_CurrentCubeIdx - m_CurrentRow;
			m_CurrentRow--;
			auto* graphics = m_GameObject->GetComponent<dae::GraphicsComponent>();
			graphics->SetSrcRectangle(m_QBertSpriteWidth, 0, m_QBertSpriteWidth, m_QBertSpriteHeight);
			m_Airborne = true;
			m_Subject->Notify(dae::Event::JumpUpLeft);
			return true;
		}
		return false;
	}
	return false;
}

bool QBert::MoveDownLeft()
{
	if (m_Frozen == false && m_Airborne == false)
	{
		// If QBert isn't in the last pyramid row
		if (m_CurrentRow != m_LastRow)
		{
			m_CurrentCubeIdx = m_CurrentCubeIdx + m_CurrentRow;
			m_CurrentRow++;
			auto* graphics = m_GameObject->GetComponent<dae::GraphicsComponent>();
			graphics->SetSrcRectangle(m_QBertSpriteWidth * 3, 0, m_QBertSpriteWidth, m_QBertSpriteHeight);
			m_Airborne = true;
			m_Subject->Notify(dae::Event::JumpDownLeft);
			return true;
		}
		return false;
	}
	return false;
}

bool QBert::MoveDownRight()
{
	if (m_Frozen == false && m_Airborne == false)
	{
		// If QBert isn't in the last pyramid row
		if (m_CurrentRow != m_LastRow)
		{
			m_CurrentCubeIdx = m_CurrentCubeIdx + m_CurrentRow + 1;
			m_CurrentRow++;
			auto* graphics = m_GameObject->GetComponent<dae::GraphicsComponent>();
			graphics->SetSrcRectangle(m_QBertSpriteWidth * 2, 0, m_QBertSpriteWidth, m_QBertSpriteHeight);
			m_Airborne = true;
			m_Subject->Notify(dae::Event::JumpDownRight);
			return true;
		}
		return false;
	}
	return false;
}

void QBert::JumpFinished()
{
	m_Airborne = false;
	m_Subject->Notify(dae::Event::QBertLanded);
}

void QBert::Initialize()
{
	auto* graphics = m_GameObject->GetComponent<dae::GraphicsComponent>();
	m_QBertInitialPosX = graphics->GetPosX();
	m_QBertInitialPosY = graphics->GetPosY();
}

void QBert::Update(const float)
{
}

