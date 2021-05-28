#include "UggWrongway.h"
#include "GameObject.h"
#include "GraphicsComponent.h"
#include <iostream>
#include "SoundServiceLocator.h"
#include "SoundSystem.h"


UggWrongway::UggWrongway(const std::shared_ptr<dae::GameObject>& gameObject, int nrRows, float cubesWidth, float cubesHeight,
                         float spriteWidth, float spriteHeight, int startingCube, float jumpInterval, bool isUgg, bool startingLeft)
	: m_GameObject(gameObject)
	, m_CurrentCubeIdx(startingCube)
	, m_CurrentRow(nrRows)
	, m_LastRow(nrRows)
	, m_CubesWidth(cubesWidth) 
	, m_CubesHeight(cubesHeight)
	, m_SpriteWidth(spriteWidth)
	, m_SpriteHeight(spriteHeight)
	, m_JumpInterval(jumpInterval)
	, m_IsUgg(isUgg)
	, m_StartingLeft(startingLeft)
{}

void UggWrongway::SetFrozen(bool frozen)
{
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
			m_CurrentCubeIdx = m_CurrentCubeIdx - m_CurrentRow;
			m_CurrentRow--;
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
			m_CurrentCubeIdx = m_CurrentCubeIdx - m_CurrentRow + 1;
			m_CurrentRow--;
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
			m_CurrentCubeIdx = m_CurrentCubeIdx - 1;
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
			m_CurrentCubeIdx = m_CurrentCubeIdx + 1;
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
		SoundServiceLocator::GetSoundSystem().Play("../Data/Sounds/Other Foes Jump.wav", 0.08f);
		m_Subject->Notify(dae::Event::UggWrongwayLanded);
	}

	else
		m_Subject->Notify(dae::Event::UggWrongwayFell);
}

void UggWrongway::Update(const float deltaTime)
{
	if (m_Alive)
	{
		if (m_Frozen == false)
		{
			m_JumpTimer += deltaTime;

			if (m_JumpTimer >= m_JumpInterval)
			{
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

				m_JumpTimer -= m_JumpInterval;
			}
		}
	}
}