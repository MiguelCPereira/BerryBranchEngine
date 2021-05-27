#include "Disk.h"

#include <iostream>


#include "GameObject.h"
#include "GraphicsComponent.h"
#include "QBert.h"

Disk::Disk(const std::shared_ptr<dae::GameObject>& gameObject, int rowIdx, bool isLeft, int colorIdx,
	float finalPosX, float finalPosY, float finalQbertPosY, float spriteWidth, float spriteHeight)
	: m_GameObject (gameObject)
	, m_QBertComp ()
	, m_QBertGraphics()
	, m_RowIdx(rowIdx)
	, m_IsLeft(isLeft)
	, m_ColorIdx(colorIdx)
	, m_Activated(false)
	, m_MovingSpeed(100.f)
	, m_InitialPosX(gameObject->GetComponent<dae::GraphicsComponent>()->GetPosX())
	, m_InitialPosY(gameObject->GetComponent<dae::GraphicsComponent>()->GetPosY())
	, m_FinalPosX(finalPosX)
	, m_FinalPosY(finalPosY)
	, m_FinalQBertPosY(finalQbertPosY)
	, m_MidFlightPosX()
	, m_MidFlightPosY()
	, m_QBertGraphAdjustmentX()
	, m_QBertGraphAdjustmentY()
	, m_MovementXIncomplete(true)
	, m_MovementYIncomplete(true)
	, m_FinalPositionReached(false)
	, m_HasBeenUsed(false)

	, m_TimeSinceLastFrame(0.f)
	, m_CurrentFrame(0)
	, m_NrFrames(4)
	, m_FPS(9)
	, m_SpriteWidth(spriteWidth)
	, m_SpriteHeight(spriteHeight)
{
}

Disk::~Disk()
{
	m_QBertComp = nullptr;
}


void Disk::Activate(QBert* qBertComp, dae::GraphicsComponent* qBertGraphics)
{
	m_QBertComp = qBertComp;
	m_QBertComp->SetFrozen(true);
	auto* graphics = m_GameObject->GetComponent<dae::GraphicsComponent>();
	m_QBertComp = qBertComp;
	m_QBertGraphics = qBertGraphics;
	m_QBertGraphAdjustmentX = m_QBertGraphics->GetPosX() - graphics->GetPosX();
	m_QBertGraphAdjustmentY = m_QBertGraphics->GetPosY() - graphics->GetPosY();
	m_MidFlightPosX = m_InitialPosX;
	m_MidFlightPosY = m_InitialPosY;
	m_Activated = true;
}

void Disk::GetDeleted() const
{
	m_GameObject->RemoveAllComponents();
}


void Disk::Update(const float deltaTime)
{
	if (m_HasBeenUsed == false)
	{
		// Idle Spinning Animation
		m_TimeSinceLastFrame += deltaTime;

		if (m_TimeSinceLastFrame >= 1.f / float(m_FPS))
		{
			m_TimeSinceLastFrame -= 1.f / float(m_FPS);

			m_GameObject->GetComponent<dae::GraphicsComponent>()->SetSrcRectangle(float(m_ColorIdx * 5) * m_SpriteWidth + m_CurrentFrame * m_SpriteWidth, 0, m_SpriteWidth, m_SpriteHeight);
			m_CurrentFrame++;

			if (m_CurrentFrame >= m_NrFrames)
				m_CurrentFrame = 0;
		}


		// Actual Functionality
		if (m_Activated)
		{
			if (m_FinalPositionReached == false)
			{
				// Movement in the X-Axis
				if (m_MovementXIncomplete)
				{
					if (m_InitialPosX < m_FinalPosX) // If it needs to move right
					{
						if (m_MidFlightPosX < m_FinalPosX)
							m_MidFlightPosX += m_MovingSpeed * deltaTime;
						else
						{
							m_MidFlightPosX = m_FinalPosX;
							m_MovementXIncomplete = false;
						}
					}
					else // If it needs to move left
					{
						if (m_MidFlightPosX > m_FinalPosX)
							m_MidFlightPosX -= m_MovingSpeed * deltaTime;
						else
						{
							m_MidFlightPosX = m_FinalPosX;
							m_MovementXIncomplete = false;
						}
					}
				}


				// Movement in the Y-Axis
				if (m_MovementYIncomplete)
				{
					if (m_MidFlightPosY > m_FinalPosY)
						m_MidFlightPosY -= m_MovingSpeed * deltaTime;
					else
					{
						m_MidFlightPosY = m_FinalPosY;
						m_MovementYIncomplete = false;
					}
				}


				// Actually move the graphics
				m_GameObject->GetComponent<dae::GraphicsComponent>()->SetPosition(m_MidFlightPosX, m_MidFlightPosY);
				m_QBertGraphics->SetPosition(m_MidFlightPosX + m_QBertGraphAdjustmentX, m_MidFlightPosY + m_QBertGraphAdjustmentY);



				// Stop the animation if the movement is complete
				if (m_MovementXIncomplete == false && m_MovementYIncomplete == false)
				{
					m_GameObject->GetComponent<dae::GraphicsComponent>()->SetPosition(-50.f, -50.f);
					m_FinalPositionReached = true;
				}
			}
			else // QBert already falling into position
			{
				if (m_QBertGraphics->GetPosY() < m_FinalQBertPosY) // Falling
				{
					m_MidFlightPosY += m_MovingSpeed * deltaTime;
					m_QBertGraphics->SetPosition(m_MidFlightPosX + m_QBertGraphAdjustmentX, m_MidFlightPosY + m_QBertGraphAdjustmentY);
				}
				else // Reached the 1st cube
				{
					m_QBertGraphics->SetPosition(m_MidFlightPosX + m_QBertGraphAdjustmentX, m_MidFlightPosY + m_QBertGraphAdjustmentY);
					m_QBertGraphics->SetPosition(m_MidFlightPosX + m_QBertGraphAdjustmentX, m_FinalQBertPosY);
					m_Activated = false;
					m_HasBeenUsed = true;
					m_Subject->Notify(dae::Event::DiskFlightEnded);
				}
			}
		}
	}
}



