#include "Cube.h"
#include "GameObject.h"
#include "GraphicsComponent.h"

Cube::Cube(const std::shared_ptr<dae::GameObject>& gameObject, int colorIdx, int level, float cubeSpriteWidth, float cubeSpriteHeight)
	: m_GameObject(gameObject)
	, m_Turned(false)
	, m_HalfTurned(false)
	, m_ColorIdx(colorIdx)
	, m_Level(level)
	, m_CubeSpriteWidth(cubeSpriteWidth)
	, m_CubeSpriteHeight(cubeSpriteHeight)
{
}

bool Cube::TurnCube()
{
	if (m_Turned == false)
	{
		if (m_Level == 1)
		{
			// Turn cube into the 2nd row color (yellow, blue, dark grey, grey-yellow, no-base blue or dark blue)
			m_GameObject->GetComponent<dae::GraphicsComponent>()->SetSrcRectangle(float(m_ColorIdx) * m_CubeSpriteWidth, m_CubeSpriteHeight, m_CubeSpriteWidth, m_CubeSpriteHeight);
			m_Turned = true;
		}
		else if (m_Level == 2)
		{
			if (m_HalfTurned)
			{
				// Turn cube into the 3rd row color (red, green, blue, purple, pink or dark purple)
				m_GameObject->GetComponent<dae::GraphicsComponent>()->SetSrcRectangle(float(m_ColorIdx) * m_CubeSpriteWidth, m_CubeSpriteHeight * 2, m_CubeSpriteWidth, m_CubeSpriteHeight);
				m_Turned = true;
			}
			else
			{
				// Turn cube into the 2nd row color (yellow, blue, dark grey, grey-yellow, no-base blue or dark blue)
				m_GameObject->GetComponent<dae::GraphicsComponent>()->SetSrcRectangle(float(m_ColorIdx) * m_CubeSpriteWidth, m_CubeSpriteHeight, m_CubeSpriteWidth, m_CubeSpriteHeight);
				m_HalfTurned = true;
			}
		}
		else
		{
			// Turn cube into the 2nd row color (yellow, blue, dark grey, grey-yellow, no-base blue or dark blue)
			m_GameObject->GetComponent<dae::GraphicsComponent>()->SetSrcRectangle(float(m_ColorIdx) * m_CubeSpriteWidth, m_CubeSpriteHeight, m_CubeSpriteWidth, m_CubeSpriteHeight);
			m_Turned = true;
		}
		
		return true;
	}
	else
	{
		if (m_Level == 3)
		{
			// Turn cube into the 1st row color (blue, yellow, white, light-blue, no-base yellow or baby-blue)
			m_GameObject->GetComponent<dae::GraphicsComponent>()->SetSrcRectangle(float(m_ColorIdx) * m_CubeSpriteWidth, 0, m_CubeSpriteWidth, m_CubeSpriteHeight);
			m_Turned = false;
		}

		return false;
	}
}

void Cube::SlickSamTurnCube()
{
	if (m_Turned)
	{
		if (m_Level == 1)
		{
			// Turn cube into the 1st row color (blue, yellow, white, light-blue, no-base yellow or baby-blue)
			m_GameObject->GetComponent<dae::GraphicsComponent>()->SetSrcRectangle(float(m_ColorIdx) * m_CubeSpriteWidth, 0, m_CubeSpriteWidth, m_CubeSpriteHeight);
		}
		else if (m_Level == 2)
		{
			// Turn cube into the 2nd row color (yellow, blue, dark grey, grey-yellow, no-base blue or dark blue)
			m_GameObject->GetComponent<dae::GraphicsComponent>()->SetSrcRectangle(float(m_ColorIdx) * m_CubeSpriteWidth, m_CubeSpriteHeight, m_CubeSpriteWidth, m_CubeSpriteHeight);
			m_HalfTurned = true;
		}
		else
		{
			// Turn cube into the 1st row color (blue, yellow, white, light-blue, no-base yellow or baby-blue)
			m_GameObject->GetComponent<dae::GraphicsComponent>()->SetSrcRectangle(float(m_ColorIdx) * m_CubeSpriteWidth, 0, m_CubeSpriteWidth, m_CubeSpriteHeight);
		}

		m_Turned = false;
	}
	else
	{
		if (m_Level == 2)
		{
			if (m_HalfTurned)
			{
				// Turn cube into the 1st row color (blue, yellow, white, light-blue, no-base yellow or baby-blue)
				m_GameObject->GetComponent<dae::GraphicsComponent>()->SetSrcRectangle(float(m_ColorIdx) * m_CubeSpriteWidth, 0, m_CubeSpriteWidth, m_CubeSpriteHeight);
				m_HalfTurned = false;
			}
		}
	}
}

void Cube::MakeCube1stColor() const
{
	m_GameObject->GetComponent<dae::GraphicsComponent>()->SetSrcRectangle(float(m_ColorIdx) * m_CubeSpriteWidth, 0, m_CubeSpriteWidth, m_CubeSpriteHeight);
}

void Cube::MakeCube2ndColor() const
{
	m_GameObject->GetComponent<dae::GraphicsComponent>()->SetSrcRectangle(float(m_ColorIdx) * m_CubeSpriteWidth, m_CubeSpriteHeight, m_CubeSpriteWidth, m_CubeSpriteHeight);
}

void Cube::MakeCube3rdColor() const
{
	m_GameObject->GetComponent<dae::GraphicsComponent>()->SetSrcRectangle(float(m_ColorIdx) * m_CubeSpriteWidth, m_CubeSpriteHeight * 2, m_CubeSpriteWidth, m_CubeSpriteHeight);
}

void Cube::Update(const float)
{
}