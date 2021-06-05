#include "QBert.h"
#include <iostream>
#include "GameObject.h"
#include "GraphicsComponent.h"
#include "SoundServiceLocator.h"
#include "SoundSystem.h"


QBert::QBert(const std::shared_ptr<dae::GameObject>& gameObject, const std::shared_ptr<dae::GameObject>& cursesGameObject,
             int nrRows, float qBertSpriteWidth, float qBertSpriteHeight, bool isPlayerOne)
	: m_GameObject(gameObject)
	, m_CursesGameObject(cursesGameObject)
	, m_LastRow(nrRows)
	, m_QBertSpriteWidth(qBertSpriteWidth)
	, m_QBertSpriteHeight(qBertSpriteHeight)
	, m_QBertInitialPosX()
	, m_QBertInitialPosY()
	, m_PosXBeforeHidden()
	, m_PosYBeforeHidden()
	, m_IsPlayerOne(isPlayerOne)
{}


bool QBert::AreGraphicsHidden() const
{
	if (m_GameObject->GetComponent<dae::GraphicsComponent>()->GetPosX() < 0.f)
		return true;

	return false;
}

void QBert::Die()
{
	m_Lives--;
	if(m_IsPlayerOne)
		m_Subject->Notify(dae::Event::QBertDiedP1);
	else
		m_Subject->Notify(dae::Event::QBertDiedP2);
}

void QBert::ResetGameVariables()
{
	m_Lives = m_MaxLives;
	m_Score = 0;
}

void QBert::ResetPosition()
{
	m_CurrentCubeIdx = 1;
	m_CurrentRow = 1;
	m_GameObject->GetComponent<dae::GraphicsComponent>()->SetPosition(m_QBertInitialPosX, m_QBertInitialPosY);
	
	if(m_IsPlayerOne)
		m_GameObject->GetComponent<dae::GraphicsComponent>()->SetSrcRectangle(m_QBertSpriteWidth * 2, 0, m_QBertSpriteWidth, m_QBertSpriteHeight);
	else
		m_GameObject->GetComponent<dae::GraphicsComponent>()->SetSrcRectangle(m_QBertSpriteWidth * 3, 0, m_QBertSpriteWidth, m_QBertSpriteHeight);
}

void QBert::RevertToLastPosition()
{
	m_JumpedOff = false;
	m_GameObject->GetComponent<dae::GraphicsComponent>()->SetPosition(m_PosXBeforeFalling, m_PosYBeforeFalling);
}

void QBert::SetFrozen(bool frozen)
{
	if(frozen)
		m_Subject->Notify(dae::Event::EntityFrozen);
	else
		m_Subject->Notify(dae::Event::EntityUnfrozen);
	
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

void QBert::BackToGround()
{
	m_Airborne = false;
	m_JumpedOff = false;
}

void QBert::SetNewPositionIndexes(int cubeIdx, int rowNr)
{
	m_CurrentCubeIdx = cubeIdx;
	m_CurrentRow = rowNr;
	m_JumpedToCubeIdx = cubeIdx;
	m_JumpedToRowIdx = rowNr;
}

void QBert::ScoreIncrease(int gainedPoints)
{
	m_Score += gainedPoints;
	if (m_IsPlayerOne)
		m_Subject->Notify(dae::Event::ScoreIncreasedP1);
	else
		m_Subject->Notify(dae::Event::ScoreIncreasedP2);
}

void QBert::SetIsInDisk(bool inDisk)
{
	m_IsInDisk = inDisk;
}

bool QBert::IsInLeftBorder() const
{
	
	return m_CurrentCubeIdx == m_CurrentRow * (m_CurrentRow + 1) / 2 - m_CurrentRow + 1 || m_CurrentCubeIdx == 1;
}

bool QBert::IsInRightBorder() const
{
	return m_CurrentCubeIdx == m_CurrentRow * (m_CurrentRow + 1) / 2;
}

bool QBert::MoveUpRight()
{
	if (m_Frozen == false && m_Airborne == false)
	{
		auto* graphics = m_GameObject->GetComponent<dae::GraphicsComponent>();
		
		if (IsInRightBorder() == false)
		{
			m_JumpedToCubeIdx = m_CurrentCubeIdx - m_CurrentRow + 1;
			m_JumpedToRowIdx = m_CurrentRow - 1;
			m_JumpedOff = false;
		}
		else
		{
			m_PosXBeforeFalling = graphics->GetPosX();
			m_PosYBeforeFalling = graphics->GetPosY();
			m_LastJumpedOffLeft = false;
			m_LastJumpedOffDown = false;
			m_JumpedOff = true;
		}

		graphics->SetSrcRectangle(0, 0, m_QBertSpriteWidth, m_QBertSpriteHeight);
		m_Airborne = true;
		m_Subject->Notify(dae::Event::JumpUpRight);
		
		if (m_JumpedOff)
			return true;
		else
			return false;
	}
	return false;
}

bool QBert::MoveUpLeft()
{
	if (m_Frozen == false && m_Airborne == false)
	{
		auto* graphics = m_GameObject->GetComponent<dae::GraphicsComponent>();
		
		if (IsInLeftBorder() == false)
		{
			m_JumpedToCubeIdx = m_CurrentCubeIdx - m_CurrentRow;
			m_JumpedToRowIdx = m_CurrentRow - 1;
			m_JumpedOff = false;
		}
		else
		{
			m_PosXBeforeFalling = graphics->GetPosX();
			m_PosYBeforeFalling = graphics->GetPosY();
			m_LastJumpedOffLeft = true;
			m_LastJumpedOffDown = false;
			m_JumpedOff = true;
		}

		graphics->SetSrcRectangle(m_QBertSpriteWidth, 0, m_QBertSpriteWidth, m_QBertSpriteHeight);
		m_Airborne = true;
		m_Subject->Notify(dae::Event::JumpUpLeft);
		
		if (m_JumpedOff)
			return true;
		else
			return false;
	}
	return false;
}

bool QBert::MoveDownLeft()
{
	if (m_Frozen == false && m_Airborne == false)
	{
		auto* graphics = m_GameObject->GetComponent<dae::GraphicsComponent>();
		
		// If QBert isn't in the last pyramid row
		if (m_CurrentRow != m_LastRow)
		{
			m_JumpedToCubeIdx = m_CurrentCubeIdx + m_CurrentRow;
			m_JumpedToRowIdx = m_CurrentRow + 1;
			m_JumpedOff = false;
		}
		else
		{
			m_PosXBeforeFalling = graphics->GetPosX();
			m_PosYBeforeFalling = graphics->GetPosY();
			m_LastJumpedOffDown = true;
			m_JumpedOff = true;
		}

		graphics->SetSrcRectangle(m_QBertSpriteWidth * 3, 0, m_QBertSpriteWidth, m_QBertSpriteHeight);
		m_Airborne = true;
		m_Subject->Notify(dae::Event::JumpDownLeft);

		if (m_JumpedOff)
			return true;
		else
			return false;
	}
	return false;
}

bool QBert::MoveDownRight()
{
	if (m_Frozen == false && m_Airborne == false)
	{
		auto* graphics = m_GameObject->GetComponent<dae::GraphicsComponent>();
		
		// If QBert isn't in the last pyramid row
		if (m_CurrentRow != m_LastRow)
		{
			m_JumpedToCubeIdx = m_CurrentCubeIdx + m_CurrentRow + 1;
			m_JumpedToRowIdx = m_CurrentRow + 1;
			m_JumpedOff = false;
		}
		else
		{
			m_PosXBeforeFalling = graphics->GetPosX();
			m_PosYBeforeFalling = graphics->GetPosY();
			m_LastJumpedOffDown = true;
			m_JumpedOff = true;
		}

		graphics->SetSrcRectangle(m_QBertSpriteWidth * 2, 0, m_QBertSpriteWidth, m_QBertSpriteHeight);
		m_Airborne = true;
		m_Subject->Notify(dae::Event::JumpDownRight);
		
		if (m_JumpedOff)
			return true;
		else
			return false;
	}
	return false;
}

void QBert::JumpFinished()
{
	if (m_JumpedOff)
	{
		if(m_IsPlayerOne)
			m_Subject->Notify(dae::Event::QBertFellP1);
		else
			m_Subject->Notify(dae::Event::QBertFellP2);
	}
	else
	{
		m_CurrentCubeIdx = m_JumpedToCubeIdx;
		m_CurrentRow = m_JumpedToRowIdx;
		SoundServiceLocator::GetSoundSystem().Play("../Data/Sounds/QBert Jump.wav", 0.1f);
		m_Airborne = false;
		if (m_IsPlayerOne)
			m_Subject->Notify(dae::Event::QBertLandedP1);
		else
			m_Subject->Notify(dae::Event::QBertLandedP2);
	}
}

void QBert::PauseGame() const
{
	m_Subject->Notify(dae::Event::PausePressed);
}

void QBert::BackToMenu() const
{
	m_Subject->Notify(dae::Event::BackToMenu);
}

void QBert::AnimationStopped() const
{
	m_Subject->Notify(dae::Event::EntityAnimationStopped);
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

