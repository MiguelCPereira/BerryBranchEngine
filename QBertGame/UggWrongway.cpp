#include "UggWrongway.h"
#include "GameObject.h"
#include "GraphicsComponent.h"
#include "SoundServiceLocator.h"
#include "SoundSystem.h"


UggWrongway::UggWrongway(const std::shared_ptr<dae::GameObject>& gameObject, int nrRows, float spriteWidth, float spriteHeight,
	int startingCube, float jumpInterval, bool isUgg, bool startingLeft)
	: m_GameObject(gameObject)

	, m_Alive(true)
	, m_Airborne(true)
	, m_Frozen(false)

	, m_CurrentCubeIdx(startingCube)
	, m_CurrentRow(nrRows)

	, m_JumpedToCubeIdx(startingCube)
	, m_JumpedToRowIdx(nrRows)

	, m_SpriteWidth(spriteWidth)
	, m_SpriteHeight(spriteHeight)

	, m_JumpTimer(0.f)
	, m_JumpInterval(jumpInterval)

	, m_IsUgg(isUgg)
	, m_StartingLeft(startingLeft)
	, m_CurrentState(UggWrongState::ST_FallingIntoSpawn)

	, m_FallTime(0.46f)
	, m_FallHeightWidth(90.f)
	, m_FallTimer(0.f)
	, m_FinalLandingPosX()
	, m_FinalLandingPosY()
	, m_TimeSinceLastFrame(0.f)
	, m_FPS(50)
{}

void UggWrongway::SetFrozen(bool frozen)
{
	if (frozen)
		m_Subject->Notify(dae::Event::EntityFrozen);
	else
		m_Subject->Notify(dae::Event::EntityUnfrozen);
	
	m_Frozen = frozen;
}

void UggWrongway::Die() const
{
	//Play Sound
	m_GameObject->RemoveAllComponents();
}

bool UggWrongway::MoveUpLeft()
{
	if (m_Frozen == false && m_Airborne == false)
	{
		// If Ugg/Wrongway isn't in the beginning of any of the pyramid rows, change the pos index
		if (m_CurrentCubeIdx != m_CurrentRow * (m_CurrentRow + 1) / 2 - m_CurrentRow + 1 && m_CurrentCubeIdx != 1)
		{
			m_JumpedToCubeIdx = m_CurrentCubeIdx - m_CurrentRow;
			m_JumpedToRowIdx = m_CurrentRow - 1;
		}
		else // Else, make them jump out of the map
		{
			m_Alive = false;
		}

		auto* graphics = m_GameObject->GetComponent<dae::GraphicsComponent>();

		if (m_IsUgg)
			graphics->SetSrcRectangle(m_SpriteWidth * 3, 0, m_SpriteWidth, m_SpriteHeight);
		else
			graphics->SetSrcRectangle(m_SpriteWidth * 3, m_SpriteHeight, m_SpriteWidth, m_SpriteHeight);

		m_Airborne = true;
		m_Subject->Notify(dae::Event::JumpUpLeft);

		if (m_Alive)
			return true;
		else
			return false;
	}
	return false;
}

bool UggWrongway::MoveUpRight()
{
	if (m_Frozen == false && m_Airborne == false)
	{
		// If Ugg/Wrongway isn't in the end of any of the pyramid rows, change the pos index
		if (m_CurrentCubeIdx != m_CurrentRow * (m_CurrentRow + 1) / 2)
		{
			m_JumpedToCubeIdx = m_CurrentCubeIdx - m_CurrentRow + 1;
			m_JumpedToRowIdx = m_CurrentRow - 1;
		}
		else // Else, make them jump out of the map
		{
			m_Alive = false;
		}

		auto* graphics = m_GameObject->GetComponent<dae::GraphicsComponent>();

		if (m_IsUgg)
			graphics->SetSrcRectangle(m_SpriteWidth, 0, m_SpriteWidth, m_SpriteHeight);
		else
			graphics->SetSrcRectangle(m_SpriteWidth, m_SpriteHeight, m_SpriteWidth, m_SpriteHeight);

		m_Airborne = true;
		m_Subject->Notify(dae::Event::JumpUpRight);

		if (m_Alive)
			return true;
		else
			return false;
	}
	return false;
}

bool UggWrongway::MoveLeft()
{
	if (m_Frozen == false && m_Airborne == false)
	{
		// If Ugg/Wrongway isn't in the beginning of any of the pyramid rows, change the pos idx
		if (m_CurrentCubeIdx != m_CurrentRow * (m_CurrentRow + 1) / 2 - m_CurrentRow + 1 && m_CurrentCubeIdx != 1)
		{
			m_JumpedToCubeIdx = m_CurrentCubeIdx - 1;
			m_JumpedToRowIdx = m_CurrentRow;
		}
		else // Else, make them jump out of the map
			m_Alive = false;

		auto* graphics = m_GameObject->GetComponent<dae::GraphicsComponent>();

		if (m_IsUgg)
			graphics->SetSrcRectangle(m_SpriteWidth * 2, 0, m_SpriteWidth, m_SpriteHeight);
		else
			graphics->SetSrcRectangle(m_SpriteWidth * 2, m_SpriteHeight, m_SpriteWidth, m_SpriteHeight);

		m_Airborne = true;
		m_Subject->Notify(dae::Event::JumpLeft);

		if (m_Alive)
			return true;
		else
			return false;
	}
	return false;
}

bool UggWrongway::MoveRight()
{
	if (m_Frozen == false && m_Airborne == false)
	{
		// If Ugg/Wrongway isn't in the end of any of the pyramid rows, change the pos index
		if (m_CurrentCubeIdx != m_CurrentRow * (m_CurrentRow + 1) / 2)
		{
			m_JumpedToCubeIdx = m_CurrentCubeIdx + 1;
			m_JumpedToRowIdx = m_CurrentRow;
		}
		else // Else, make them jump out of the map
			m_Alive = false;

		auto* graphics = m_GameObject->GetComponent<dae::GraphicsComponent>();

		if (m_IsUgg)
			graphics->SetSrcRectangle(0, 0, m_SpriteWidth, m_SpriteHeight);
		else
			graphics->SetSrcRectangle(0, m_SpriteHeight, m_SpriteWidth, m_SpriteHeight);

		m_Airborne = true;
		m_Subject->Notify(dae::Event::JumpRight);

		if (m_Alive)
			return true;
		else
			return false;
	}
	return false;
}

void UggWrongway::JumpFinished()
{
	m_Airborne = false;
	
	if (m_Alive)
	{
		m_CurrentCubeIdx = m_JumpedToCubeIdx;
		m_CurrentRow = m_JumpedToRowIdx;
		SoundServiceLocator::GetSoundSystem().Play("../Data/Sounds/Other Foes Jump.wav", 0.08f);
		m_Subject->Notify(dae::Event::UggWrongwayLanded);
	}

	else
		m_Subject->Notify(dae::Event::UggWrongwayFell);
}

bool UggWrongway::FallIntoSpawnPos(float deltaTime)
{
	auto* graphics = m_GameObject->GetComponent<dae::GraphicsComponent>();
	const auto toTravelInSec = m_FallHeightWidth / m_FallTime;

	m_TimeSinceLastFrame += deltaTime;
	m_FallTimer += deltaTime;

	// Change the position 50 times per frame (or whoever much m_FPS is set as)
	if (m_TimeSinceLastFrame >= 1.f / float(m_FPS) && m_FallTimer < m_FallTime)
	{
		m_TimeSinceLastFrame -= 1.f / float(m_FPS);
		const float toTravelInFrame = toTravelInSec / float(m_FPS);
		
		if(m_StartingLeft)
			graphics->SetPosition(graphics->GetPosX() + toTravelInFrame, graphics->GetPosY() - toTravelInFrame);
		else
			graphics->SetPosition(graphics->GetPosX() - toTravelInFrame, graphics->GetPosY() - toTravelInFrame);
	}

	// Stop the animation if the movement is complete
	if (m_FallTimer >= m_FallTime)
	{
		m_FallTimer = 0.f;
		graphics->SetPosition(m_FinalLandingPosX, m_FinalLandingPosY);
		m_Airborne = false;
		return true;
	}

	return false;
}

void UggWrongway::Initialize()
{
	// Store all the needed info in the member variables
	auto* graphics = m_GameObject->GetComponent<dae::GraphicsComponent>();
	m_FinalLandingPosX = graphics->GetPosX();
	m_FinalLandingPosY = graphics->GetPosY();

	if(m_StartingLeft)
		graphics->SetPosition(graphics->GetPosX() - m_FallHeightWidth, graphics->GetPosY() + m_FallHeightWidth);
	else
		graphics->SetPosition(graphics->GetPosX() + m_FallHeightWidth, graphics->GetPosY() + m_FallHeightWidth);
}

void UggWrongway::Update(const float deltaTime)
{
	if (m_Frozen == false)
	{
		switch (m_CurrentState)
		{
		case UggWrongState::ST_FallingIntoSpawn:
			if (FallIntoSpawnPos(deltaTime)) // This function will only return true if the fall animation is done
			{
				m_CurrentState = UggWrongState::ST_Waiting;
				JumpFinished();
			}
			break;

		case UggWrongState::ST_Waiting:
			m_JumpTimer += deltaTime;

			if (m_JumpTimer >= m_JumpInterval)
			{
				m_JumpTimer = 0;
				m_CurrentState = UggWrongState::ST_Jumping;
			}
			break;

		case UggWrongState::ST_Jumping:
			// A random 50/50 chance of Ugg/Wrongway moving to the side or up
			if ((rand() % 2) + 1 == 1)
			{
				if (m_StartingLeft)
					MoveUpRight();
				else
					MoveUpLeft();
			}
			else
			{
				if (m_StartingLeft)
					MoveRight();
				else
					MoveLeft();
			}

			m_CurrentState = UggWrongState::ST_Waiting;
			break;
		}
	}
}