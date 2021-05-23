#include "SlickSam.h"
#include "GameObject.h"
#include "GraphicsComponent.h"
#include <iostream>


SlickSam::SlickSam(const std::shared_ptr<dae::GameObject>& gameObject, int nrRows, float cubesWidth, float cubesHeight,
	float spriteWidth, float spriteHeight, int startingCube, float jumpInterval, bool isSlick)
	: m_GameObject(gameObject)
	, m_CurrentCubeIdx(startingCube)
	, m_LastRow(nrRows)
	, m_CubesWidth(cubesWidth)
	, m_CubesHeight(cubesHeight)
	, m_SpriteWidth(spriteWidth)
	, m_SpriteHeight(spriteHeight)
	, m_JumpInterval(jumpInterval)
	, m_IsSlick(isSlick)
{}

void SlickSam::SetFrozen(bool frozen)
{
	m_Frozen = frozen;
}

void SlickSam::Die() const
{	
	if (m_IsSlick)
		std::cout << "Slick died\n";
	else
		std::cout << "Sam died\n";
	
	//Play Animation and Sound
	
	m_GameObject->RemoveAllComponents();
}

bool SlickSam::MoveDownLeft()
{
	if (m_Frozen == false)
	{
		// If Slick/Sam isn't in the last pyramid row
		if (m_CurrentRow != m_LastRow)
		{
			m_CurrentCubeIdx = m_CurrentCubeIdx + m_CurrentRow;
			m_CurrentRow++;
			auto* graphics = m_GameObject->GetComponent<dae::GraphicsComponent>();
			graphics->SetPosition(graphics->GetPosX() - m_CubesWidth / 2.f, graphics->GetPosY() + m_CubesHeight * 0.75f);

			if (m_IsSlick)
				graphics->SetSrcRectangle(0, 0, m_SpriteWidth, m_SpriteHeight);
			else
				graphics->SetSrcRectangle(0, m_SpriteHeight, m_SpriteWidth, m_SpriteHeight);

			m_Subject->Notify(dae::Event::SlickSamMove);
			return true;
		}
		else
		{
			// Make them jump out of the map
			m_Alive = false;
			m_Subject->Notify(dae::Event::SlickSamFell);
			return false;
		}
	}
	return false;
}

bool SlickSam::MoveDownRight()
{
	if (m_Frozen == false)
	{
		// If Slick/Sam isn't in the last pyramid row
		if (m_CurrentRow != m_LastRow)
		{
			m_CurrentCubeIdx = m_CurrentCubeIdx + m_CurrentRow + 1;
			m_CurrentRow++;
			auto* graphics = m_GameObject->GetComponent<dae::GraphicsComponent>();
			graphics->SetPosition(graphics->GetPosX() + m_CubesWidth / 2.f, graphics->GetPosY() + m_CubesHeight * 0.75f);

			if (m_IsSlick)
				graphics->SetSrcRectangle(m_SpriteWidth, 0, m_SpriteWidth, m_SpriteHeight);
			else
				graphics->SetSrcRectangle(m_SpriteWidth, m_SpriteHeight, m_SpriteWidth, m_SpriteHeight);

			m_Subject->Notify(dae::Event::SlickSamMove);
			return true;
		}
		else
		{
			// Make them jump out of the map
			m_Alive = false;
			m_Subject->Notify(dae::Event::SlickSamFell);
			return false;
		}
	}
	return false;
}

void SlickSam::Update(const float deltaTime)
{
	if (m_Alive == true && m_Frozen == false)
	{
		m_JumpTimer += deltaTime;

		if (m_JumpTimer >= m_JumpInterval)
		{
			// A random 50/50 chance of Slick/Sam falling to the right or left

			if ((rand() % 2) + 1 == 1)
				MoveDownRight();
			else
				MoveDownLeft();

			m_JumpTimer -= m_JumpInterval;
		}
	}
}
