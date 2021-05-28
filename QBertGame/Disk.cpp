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
	, m_FlightTime(1.1f)
	, m_QBertFallSpeed(200.f)
	, m_InitialPosX(gameObject->GetComponent<dae::GraphicsComponent>()->GetPosX())
	, m_InitialPosY(gameObject->GetComponent<dae::GraphicsComponent>()->GetPosY())
	, m_FinalPosX(finalPosX)
	, m_FinalPosY(finalPosY)
	, m_FinalQBertPosY(finalQbertPosY)
	, m_MidFlightPosX()
	, m_MidFlightPosY()
	, m_QBertGraphAdjustmentX()
	, m_QBertGraphAdjustmentY()
	, m_FinalPositionReached(false)
	, m_HasBeenUsed(false)

	, m_FPSIdle(9)
	, m_FPSFlight(50)
	, m_MidFlightTime(0.f)
	, m_TimeSinceLastFrameFlight(0.f)
	, m_TimeSinceLastFrameIdle(0.f)
	, m_CurrentFrame(0)
	, m_NrFrames(4)
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
		m_TimeSinceLastFrameIdle += deltaTime;

		if (m_TimeSinceLastFrameIdle >= 1.f / float(m_FPSIdle))
		{
			m_TimeSinceLastFrameIdle -= 1.f / float(m_FPSIdle);

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
				const auto toTravelInSecX = (m_FinalPosX - m_InitialPosX) / m_FlightTime;
				const auto toTravelInSecY = (m_FinalPosY - m_InitialPosY) / m_FlightTime;

				m_TimeSinceLastFrameFlight += deltaTime;
				m_MidFlightTime += deltaTime;

				if (m_TimeSinceLastFrameFlight >= 1.f / float(m_FPSFlight) && m_MidFlightTime < m_FlightTime)
				{
					m_TimeSinceLastFrameFlight -= 1.f / float(m_FPSFlight);
					m_MidFlightPosX += toTravelInSecX / float(m_FPSFlight);
					m_MidFlightPosY += toTravelInSecY / float(m_FPSFlight);
				}


				// Actually move the graphics
				m_GameObject->GetComponent<dae::GraphicsComponent>()->SetPosition(m_MidFlightPosX, m_MidFlightPosY);
				m_QBertGraphics->SetPosition(m_MidFlightPosX + m_QBertGraphAdjustmentX, m_MidFlightPosY + m_QBertGraphAdjustmentY);



				// Stop the animation if the movement is complete
				if (m_MidFlightTime >= m_FlightTime)
				{
					m_GameObject->GetComponent<dae::GraphicsComponent>()->SetPosition(-50.f, -50.f);
					m_FinalPositionReached = true;
				}
			}
			else // QBert already falling into position
			{
				if (m_QBertGraphics->GetPosY() < m_FinalQBertPosY) // Falling
				{
					m_MidFlightPosY += m_QBertFallSpeed * deltaTime;
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


