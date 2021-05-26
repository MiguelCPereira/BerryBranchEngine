#include "Coily.h"
#include "GameObject.h"
#include "GraphicsComponent.h"
#include <iostream>
#include "QBert.h"

Coily::Coily(const std::shared_ptr<dae::GameObject>& gameObject, QBert* qBertComp, int nrRows, float cubesWidth,
             float cubesHeight, float spriteWidth, float spriteHeight, int startingCube, float jumpInterval)
	: m_GameObject(gameObject)
	, m_QBertComp(qBertComp)
	, m_CurrentCubeIdx(startingCube)
	, m_LastRow(nrRows)
	, m_CubesWidth(cubesWidth)
	, m_CubesHeight(cubesHeight)
	, m_SpriteWidth(spriteWidth)
	, m_SpriteHeight(spriteHeight)
	, m_JumpInterval(jumpInterval)
	, m_Direction(startingCube - 1)
{
}

void Coily::SetFrozen(bool frozen)
{
	m_Frozen = frozen;
}

void Coily::Die() const
{
	//Play Sound
	m_GameObject->RemoveAllComponents();
}

bool Coily::MoveDownLeft()
{
	if (m_Frozen == false && m_Airborne == false)
	{
		// If Coily isn't in the last pyramid row, change the pos index
		if (m_CurrentRow != m_LastRow)
		{
			m_CurrentCubeIdx = m_CurrentCubeIdx + m_CurrentRow;
			m_CurrentRow++;
		}
		else // Else, make them start hatching (but if they have already, make them jump out of the map)
		{
			if (m_IsEgg)
				m_IsTransforming = true;
			else
				m_Alive = false;
		}

		if (m_IsTransforming == false)
		{
			auto* graphics = m_GameObject->GetComponent<dae::GraphicsComponent>();

			if (m_IsEgg)
				graphics->SetSrcRectangle(m_SpriteWidth, 0, m_SpriteWidth, m_SpriteHeight);
			else
				graphics->SetSrcRectangle(m_SpriteWidth * 9, 0, m_SpriteWidth, m_SpriteHeight);

			m_Airborne = true;
			m_Direction = 1;
			m_Subject->Notify(dae::Event::JumpDownLeft);
		}

		if(m_Alive)
			return true;
		else
			return false;
	}
	return false;
}

bool Coily::MoveDownRight()
{
	if (m_Frozen == false)
	{
		// If Coily isn't in the last pyramid row, change the pos index
		if (m_CurrentRow != m_LastRow)
		{
			m_CurrentCubeIdx = m_CurrentCubeIdx + m_CurrentRow + 1;
			m_CurrentRow++;
		}
		else // Else, make them start hatching (but if they have already, make them jump out of the map)
		{
			if (m_IsEgg)
				m_IsTransforming = true;
			else
				m_Alive = false;
		}

		if (m_IsTransforming == false)
		{
			auto* graphics = m_GameObject->GetComponent<dae::GraphicsComponent>();

			if (m_IsEgg)
				graphics->SetSrcRectangle(m_SpriteWidth, 0, m_SpriteWidth, m_SpriteHeight);
			else
				graphics->SetSrcRectangle(m_SpriteWidth * 7, 0, m_SpriteWidth, m_SpriteHeight);

			m_Airborne = true;
			m_Direction = 2;
			m_Subject->Notify(dae::Event::JumpDownRight);
		}

		if (m_Alive)
			return true;
		else
			return false;
	}
	return false;
}

bool Coily::MoveUpLeft()
{
	if (m_Frozen == false && m_Airborne == false)
	{
		// If Coily isn't in the beginning of any of the pyramid rows, change the pos index
		if (m_CurrentCubeIdx != m_CurrentRow * (m_CurrentRow + 1) / 2 - m_CurrentRow + 1 && m_CurrentCubeIdx != 1)
		{
			m_CurrentCubeIdx = m_CurrentCubeIdx - m_CurrentRow;
			m_CurrentRow--;
		}
		else // Else, make them start hatching (but if they have already, make them jump out of the map)
		{
			if (m_IsEgg)
				m_IsTransforming = true;
			else
				m_Alive = false;
		}

		if (m_IsTransforming == false)
		{
			auto* graphics = m_GameObject->GetComponent<dae::GraphicsComponent>();

			if (m_IsEgg)
				graphics->SetSrcRectangle(m_SpriteWidth, 0, m_SpriteWidth, m_SpriteHeight);
			else
				graphics->SetSrcRectangle(m_SpriteWidth * 5, 0, m_SpriteWidth, m_SpriteHeight);

			m_Airborne = true;
			m_Direction = 3;
			m_Subject->Notify(dae::Event::JumpUpLeft);
		}

		if (m_Alive)
			return true;
		else
			return false;
	}
	return false;
}

bool Coily::MoveUpRight()
{
	if (m_Frozen == false && m_Airborne == false)
	{
		// If Coily isn't in the end of any of the pyramid rows, change the pos index
		if (m_CurrentCubeIdx != m_CurrentRow * (m_CurrentRow + 1) / 2)
		{
			m_CurrentCubeIdx = m_CurrentCubeIdx - m_CurrentRow + 1;
			m_CurrentRow--;
		}
		else // Else, make them start hatching (but if they have already, make them jump out of the map)
		{
			if (m_IsEgg)
				m_IsTransforming = true;
			else
				m_Alive = false;
		}

		if (m_IsTransforming == false)
		{
			auto* graphics = m_GameObject->GetComponent<dae::GraphicsComponent>();

			if (m_IsEgg)
				graphics->SetSrcRectangle(m_SpriteWidth, 0, m_SpriteWidth, m_SpriteHeight);
			else
				graphics->SetSrcRectangle(m_SpriteWidth * 3, 0, m_SpriteWidth, m_SpriteHeight);

			m_Airborne = true;
			m_Direction = 4;
			m_Subject->Notify(dae::Event::JumpUpRight);
		}

		if (m_Alive)
			return true;
		else
			return false;
	}
	return false;
}

void Coily::JumpFinished()
{
	// Set landing graphics
	auto* graphics = m_GameObject->GetComponent<dae::GraphicsComponent>();

	if (m_IsEgg)
		graphics->SetSrcRectangle(0, 0, m_SpriteWidth, m_SpriteHeight);
	else
	{
		if(m_Direction == 1)
			graphics->SetSrcRectangle(m_SpriteWidth * 8, 0, m_SpriteWidth, m_SpriteHeight);
		else if(m_Direction == 2)
			graphics->SetSrcRectangle(m_SpriteWidth * 6, 0, m_SpriteWidth, m_SpriteHeight);
		else if(m_Direction == 3)
			graphics->SetSrcRectangle(m_SpriteWidth * 4, 0, m_SpriteWidth, m_SpriteHeight);
		else
			graphics->SetSrcRectangle(m_SpriteWidth * 2, 0, m_SpriteWidth, m_SpriteHeight);
	}
	
	m_Airborne = false;

	if (m_Alive)
		m_Subject->Notify(dae::Event::CoilyLanded);
	else
		m_Subject->Notify(dae::Event::CoilyFell);
}

void Coily::Update(const float deltaTime)
{
	if (m_Alive == true && m_Frozen == false)
	{
		if(m_IsTransforming)
		{
			m_TransformTimer += deltaTime;

			if(m_TransformTimer >= m_TransformationTime)
			{
				m_IsEgg = false;
				m_IsTransforming = false;
				m_TransformTimer = 0.f;
			}
		}
		else
		{
			m_JumpTimer += deltaTime;

			if (m_JumpTimer >= m_JumpInterval)
			{
				if (m_IsEgg)
				{
					// A random 50/50 chance of Coily's egg falling to the right or left
					if ((rand() % 2) + 1 == 1)
						MoveDownRight();
					else
						MoveDownLeft();
				}
				else
				{
					int qBertNrInRow;
					int coilyNrInRow;
					const int qBertCubeIdx = m_QBertComp->GetPositionIndex();
					const int qBertRow = m_QBertComp->GetCurrentRow();
					
					
					if (qBertCubeIdx != 1)
						qBertNrInRow = qBertCubeIdx - (qBertRow * (qBertRow + 1) / 2 - qBertRow);
					else
						qBertNrInRow = 0;


					if (m_CurrentCubeIdx != 1)
						coilyNrInRow = m_CurrentCubeIdx - (m_CurrentRow * (m_CurrentRow + 1) / 2 - m_CurrentRow);
					else
						coilyNrInRow = 0;

					
					if (qBertRow > m_CurrentRow) // QBert is bellow Coily
					{
						if (qBertRow - qBertNrInRow > m_CurrentRow - coilyNrInRow) // Qbert is to Coily's Left
							MoveDownLeft();
						else // Qbert is either to Coily's Left or exactly bellow
							MoveDownRight();
					}
					else if (qBertRow < m_CurrentRow) // QBert is above Coily
					{
						if (qBertRow - qBertNrInRow > m_CurrentRow - coilyNrInRow) // Qbert is to Coily's Left
							MoveUpLeft();
						else // Qbert is either to Coily's Left or exactly above
							MoveUpRight();
					}
					else // They're both in the same row
					{
						// Coily will always move up in these situations
						// because if they went down and they happened to be in the last row
						// they would jump to their death
						if(qBertNrInRow > coilyNrInRow) // QBert is to Coily's Right
							MoveUpRight();
						else // QBert's to Coily's Left
							MoveUpLeft();
					}
					
				}

				m_JumpTimer -= m_JumpInterval;
			}
		}
	}
}



