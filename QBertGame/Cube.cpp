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

void Cube::TurnCube()
{
	if (m_Turned == false)
	{
		if (m_Level == 1)
		{
			// Turn cube yellow (or blue for 2nd color, dark grey for 3rd, grey-yellow for 4th, etc)
			m_GameObject->GetComponent<dae::GraphicsComponent>()->SetSrcRectangle(float(m_ColorIdx) * m_CubeSpriteWidth, m_CubeSpriteHeight, m_CubeSpriteWidth, m_CubeSpriteHeight);
			m_Turned = true;
		}
		else if (m_Level == 2)
		{
			if (m_HalfTurned)
			{
				// Turn cube yellow (or blue for 2nd color, dark grey for 3rd, grey-yellow for 4th, etc)
				m_GameObject->GetComponent<dae::GraphicsComponent>()->SetSrcRectangle(float(m_ColorIdx) * m_CubeSpriteWidth, m_CubeSpriteHeight, m_CubeSpriteWidth, m_CubeSpriteHeight);
				m_Turned = true;
			}
			else
			{
				// Turn cube red (or green for 2nd color, blue for 3rd, purple for 4th, etc)
				m_GameObject->GetComponent<dae::GraphicsComponent>()->SetSrcRectangle(float(m_ColorIdx) * m_CubeSpriteWidth, m_CubeSpriteHeight * 2, m_CubeSpriteWidth, m_CubeSpriteHeight);
				m_HalfTurned = true;
			}
		}
		else
		{
			// Turn cube yellow (or blue for 2nd color, dark grey for 3rd, grey-yellow for 4th, etc)
			m_GameObject->GetComponent<dae::GraphicsComponent>()->SetSrcRectangle(float(m_ColorIdx) * m_CubeSpriteWidth, m_CubeSpriteHeight, m_CubeSpriteWidth, m_CubeSpriteHeight);
			m_Turned = true;
		}
	}
	else
	{
		if (m_Level == 3)
		{
			// Turn cube blue (or yellow for 2nd color, white for 3rd, light-blue for 4th, etc)
			m_GameObject->GetComponent<dae::GraphicsComponent>()->SetSrcRectangle(float(m_ColorIdx) * m_CubeSpriteWidth, 0, m_CubeSpriteWidth, m_CubeSpriteHeight);
			m_Turned = false;
		}
	}
}

void Cube::Update(const float)
{
}