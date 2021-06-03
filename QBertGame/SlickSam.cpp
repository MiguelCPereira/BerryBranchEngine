#include "SlickSam.h"
#include "GameObject.h"
#include "GraphicsComponent.h"
#include <iostream>
#include "SoundServiceLocator.h"
#include "SoundSystem.h"


SlickSam::SlickSam(const std::shared_ptr<dae::GameObject>& gameObject, int nrRows, float spriteWidth, float spriteHeight,
	int startingCube, float jumpInterval, bool isSlick)
	: m_GameObject(gameObject)

	, m_Alive(true)
	, m_Airborne(true)
	, m_Frozen(false)

	, m_CurrentCubeIdx(startingCube)
	, m_CurrentRow(2)
	, m_LastRow(nrRows)

	, m_SpriteWidth(spriteWidth)
	, m_SpriteHeight(spriteHeight)

	, m_JumpTimer(0.f)
	, m_JumpInterval(jumpInterval)

	, m_IsSlick(isSlick)
	, m_CurrentState(SlickSamState::ST_FallingIntoSpawn)

	, m_FallTime(0.8f)
	, m_FallHeight(155.f)
	, m_FallTimer(0.f)
	, m_FinalLandingPosY()
	, m_TimeSinceLastFrame(0.f)
	, m_FPS(50)
{}

void SlickSam::SetFrozen(bool frozen)
{
	m_Frozen = frozen;
}

void SlickSam::Die() const
{	
	//Play Sound
	m_GameObject->RemoveAllComponents();
}

bool SlickSam::MoveDownLeft()
{
	if (m_Frozen == false && m_Airborne == false)
	{
		// If Slick/Sam isn't in the last pyramid row, change the pos index
		if (m_CurrentRow != m_LastRow)
		{
			m_CurrentCubeIdx = m_CurrentCubeIdx + m_CurrentRow;
			m_CurrentRow++;
		}
		else // Else, make them jump out of the map
		{
			m_Alive = false;
		}

		auto* graphics = m_GameObject->GetComponent<dae::GraphicsComponent>();

		if (m_IsSlick)
			graphics->SetSrcRectangle(0, 0, m_SpriteWidth, m_SpriteHeight);
		else
			graphics->SetSrcRectangle(0, m_SpriteHeight, m_SpriteWidth, m_SpriteHeight);

		m_Airborne = true;
		m_Subject->Notify(dae::Event::JumpDownLeft);

		if (m_Alive)
			return true;
		else
			return false;
	}
	return false;
}

bool SlickSam::MoveDownRight()
{
	if (m_Frozen == false)
	{
		// If Slick/Sam isn't in the last pyramid row, change the pos index
		if (m_CurrentRow != m_LastRow)
		{
			m_CurrentCubeIdx = m_CurrentCubeIdx + m_CurrentRow + 1;
			m_CurrentRow++;
		}
		else // Else, make them jump out of the map
		{
			m_Alive = false;
		}

		auto* graphics = m_GameObject->GetComponent<dae::GraphicsComponent>();

		if (m_IsSlick)
			graphics->SetSrcRectangle(m_SpriteWidth, 0, m_SpriteWidth, m_SpriteHeight);
		else
			graphics->SetSrcRectangle(m_SpriteWidth, m_SpriteHeight, m_SpriteWidth, m_SpriteHeight);

		m_Airborne = true;
		m_Subject->Notify(dae::Event::JumpDownRight);

		if (m_Alive)
			return true;
		else
			return false;
	}
	return false;
}

void SlickSam::JumpFinished()
{
	m_Airborne = false;
	
	if (m_Alive)
	{
		SoundServiceLocator::GetSoundSystem().Play("../Data/Sounds/Other Foes Jump.wav", 0.08f);
		m_Subject->Notify(dae::Event::SlickSamLanded);
	}
	else
		m_Subject->Notify(dae::Event::SlickSamFell);
}

bool SlickSam::FallIntoSpawnPos(float deltaTime)
{
	auto* graphics = m_GameObject->GetComponent<dae::GraphicsComponent>();
	const auto toTravelInSec = m_FallHeight / m_FallTime;

	m_TimeSinceLastFrame += deltaTime;
	m_FallTimer += deltaTime;

	// Change the position every 50 times per frame (or whoever much m_FPS is set as)
	if (m_TimeSinceLastFrame >= 1.f / float(m_FPS) && m_FallTimer < m_FallTime)
	{
		m_TimeSinceLastFrame -= 1.f / float(m_FPS);
		graphics->SetPosition(graphics->GetPosX(), graphics->GetPosY() + toTravelInSec / float(m_FPS));
	}

	// Stop the animation if the movement is complete
	if (m_FallTimer >= m_FallTime)
	{
		m_FallTimer = 0.f;
		graphics->SetPosition(graphics->GetPosX(), m_FinalLandingPosY);
		m_Airborne = false;
		return true;
	}

	return false;
}

void SlickSam::Initialize()
{
	auto* graphics = m_GameObject->GetComponent<dae::GraphicsComponent>();
	m_FinalLandingPosY = graphics->GetPosY();
	graphics->SetPosition(graphics->GetPosX(), graphics->GetPosY() - m_FallHeight);
}

void SlickSam::Update(const float deltaTime)
{
	switch (m_CurrentState)
	{
	case SlickSamState::ST_FallingIntoSpawn:
		if (FallIntoSpawnPos(deltaTime)) // This function will only return true if the fall animation is done
		{
			m_CurrentState = SlickSamState::ST_Waiting;
			JumpFinished();
		}
		break;
		
	case SlickSamState::ST_Waiting:
		m_JumpTimer += deltaTime;

		if (m_JumpTimer >= m_JumpInterval)
		{
			m_JumpTimer = 0;
			m_CurrentState = SlickSamState::ST_Jumping;
		}
		break;

	case SlickSamState::ST_Jumping:
		// A random 50/50 chance of Slick/Sam falling to the right or left
		if ((rand() % 2) + 1 == 1)
			MoveDownRight();
		else
			MoveDownLeft();

		m_CurrentState = SlickSamState::ST_Waiting;

		break;
	}
}

