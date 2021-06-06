#include "Disk.h"
#include "GameObject.h"
#include "GraphicsComponent.h"
#include "QBert.h"
#include "SoundServiceLocator.h"
#include "SoundSystem.h"

Disk::Disk(const std::shared_ptr<dae::GameObject>& gameObject, int rowIdx, bool isLeft, int colorIdx,
	float finalPosX, float finalPosY, float finalQbertPosY, float spriteWidth, float spriteHeight)
	: m_GameObject(gameObject)
	, m_QBertComp()
	, m_QBertGraphics()
	, m_RowIdx(rowIdx)
	, m_IsLeft(isLeft)
	, m_ColorIdx(colorIdx)
	, m_Activated(false)
	, m_FlightTime(2.2f)
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
	, m_Hidden(false)

	, m_FPSIdle(9)
	, m_FPSFlight(50)
	, m_MidFlightTime(0.f)
	, m_TimeSinceLastFrameFlight(0.f)
	, m_TimeSinceLastFrameIdle(0.f)
	, m_CurrentFrame(0)
	, m_NrFrames(4)
	, m_SpriteWidth(spriteWidth)
	, m_SpriteHeight(spriteHeight)

	, m_CarryingPlayerOne()
{
}

Disk::~Disk()
{
	m_QBertComp = nullptr;
}


void Disk::Activate(QBert* qBertComp, dae::GraphicsComponent* qBertGraphics, bool playerOne)
{
	SoundServiceLocator::GetSoundSystem().Play("../Data/Sounds/Disk Lift.wav", 0.1f);
	m_CarryingPlayerOne = playerOne;

	// Register QBert's components in the member variables and freeze them
	m_QBertComp = qBertComp;
	m_QBertGraphics = qBertGraphics;
	m_QBertComp->SetIsInDisk(true);
	m_QBertComp->SetFrozen(true);

	// Set required member variables
	auto* graphics = m_GameObject->GetComponent<dae::GraphicsComponent>();
	m_QBertGraphAdjustmentX = m_QBertGraphics->GetPosX() - graphics->GetPosX();
	m_QBertGraphAdjustmentY = m_QBertGraphics->GetPosY() - graphics->GetPosY();
	m_MidFlightPosX = m_InitialPosX;
	m_MidFlightPosY = m_InitialPosY;
	m_Activated = true;
}

void Disk::SetHide(bool isHidden)
{
	auto* graphics = m_GameObject->GetComponent<dae::GraphicsComponent>();

	if (isHidden)
		graphics->SetHidden(true);
	else
		graphics->SetHidden(false);

	m_Hidden = isHidden;
}

void Disk::SetFrozen(bool isFrozen)
{
	m_Frozen = isFrozen;
}

void Disk::ResetDisk()
{
	// Return the disk's graphics to their original position
	auto* graphics = m_GameObject->GetComponent<dae::GraphicsComponent>();
	graphics->SetPosition(m_InitialPosX, m_InitialPosY);

	// And reset all modified member variables
	m_Activated = false;
	m_MidFlightPosX = m_InitialPosX;
	m_MidFlightPosY = m_InitialPosY;
	m_FinalPositionReached = false;
	m_MidFlightTime = 0.f;
	m_TimeSinceLastFrameFlight = 0.f;
	m_TimeSinceLastFrameIdle = 0.f;
	m_CurrentFrame = 0;
	m_HasBeenUsed = false;
	m_Hidden = false;
}

void Disk::Die() const
{
	m_GameObject->RemoveAllComponents();
}

void Disk::Update(const float deltaTime)
{
	if (m_HasBeenUsed == false && m_Hidden == false && m_Frozen == false)
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
			if (m_FinalPositionReached == false) // If the flight animation isn't done yet
			{
				// Calculate the m_MidFlightPositions
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


				// Actually move the disk and QBert
				m_GameObject->GetComponent<dae::GraphicsComponent>()->SetPosition(m_MidFlightPosX, m_MidFlightPosY);
				m_QBertGraphics->SetPosition(m_MidFlightPosX + m_QBertGraphAdjustmentX, m_MidFlightPosY + m_QBertGraphAdjustmentY);



				// Stop the flight animation if the movement is complete
				if (m_MidFlightTime >= m_FlightTime)
				{
					// And hide the disk's graphics (without stopping the update, so
					// SetHidden() is called directly instead of the Disk class function
					SoundServiceLocator::GetSoundSystem().Play("../Data/Sounds/Disk Land.wav", 0.1f);
					m_GameObject->GetComponent<dae::GraphicsComponent>()->SetHidden(true);
					m_FinalPositionReached = true;
				}
			}
			else // Else, QBert must already be falling into the first cube
			{
				if (m_QBertGraphics->GetPosY() < m_FinalQBertPosY) // If QBert hasn't landed
				{
					// Make them fall
					m_MidFlightPosY += m_QBertFallSpeed * deltaTime;
					m_QBertGraphics->SetPosition(m_MidFlightPosX + m_QBertGraphAdjustmentX, m_MidFlightPosY + m_QBertGraphAdjustmentY);
				}
				else // Else, Qbert just landed
				{
					// Set QBert's position to the exact landing spot and deactivate the disk
					m_QBertGraphics->SetPosition(m_MidFlightPosX + m_QBertGraphAdjustmentX, m_MidFlightPosY + m_QBertGraphAdjustmentY);
					m_QBertGraphics->SetPosition(m_MidFlightPosX + m_QBertGraphAdjustmentX, m_FinalQBertPosY);
					m_Activated = false;
					m_HasBeenUsed = true;
					m_QBertComp->SetIsInDisk(false);
					
					if (m_CarryingPlayerOne)
						m_Subject->Notify(dae::Event::DiskFlightEndedP1);
					else
						m_Subject->Notify(dae::Event::DiskFlightEndedP2);
				}
			}
		}
	}
}



