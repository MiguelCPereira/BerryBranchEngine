#include "JumpingObserver.h"

#include "Coily.h"
#include "GraphicsComponent.h"
#include "QBert.h"
#include "SlickSam.h"
#include "UggWrongway.h"

JumpingObserver::JumpingObserver(QBert* qBertComp, dae::GraphicsComponent* graphicsComp, float cubesWidth, float cubesHeight)
	: m_QBertComp(qBertComp)
	, m_CoilyComp()
	, m_SlickSamComp()
	, m_UggWrongComp()
	, m_GraphicsComp(graphicsComp)
	, m_CubesWidth(cubesWidth)
	, m_CubesHeight(cubesHeight)
	, m_Jumping(false)
	, m_JumpingSpeed(300.f)
	, m_LiftoffPosX()
	, m_LiftoffPosY()
	, m_LandingPosX()
	, m_LandingPosY()
	, m_MidFlightPosX()
	, m_MidFlightPosY()
	, m_MovingRight()
	, m_MovingDown()
	, m_MovementXIncomplete()
	, m_MovementYIncomplete()
{}

JumpingObserver::JumpingObserver(Coily* coilyComp, dae::GraphicsComponent* graphicsComp, float cubesWidth, float cubesHeight)
	: m_QBertComp()
	, m_CoilyComp(coilyComp)
	, m_SlickSamComp()
	, m_UggWrongComp()
	, m_GraphicsComp(graphicsComp)
	, m_CubesWidth(cubesWidth)
	, m_CubesHeight(cubesHeight)
	, m_Jumping(false)
	, m_JumpingSpeed(200.f)
	, m_LiftoffPosX()
	, m_LiftoffPosY()
	, m_LandingPosX()
	, m_LandingPosY()
	, m_MidFlightPosX()
	, m_MidFlightPosY()
	, m_MovingRight()
	, m_MovingDown()
	, m_MovementXIncomplete()
	, m_MovementYIncomplete()
{}

JumpingObserver::JumpingObserver(SlickSam* slickSamComp, dae::GraphicsComponent* graphicsComp, float cubesWidth, float cubesHeight)
	: m_QBertComp()
	, m_CoilyComp()
	, m_SlickSamComp(slickSamComp)
	, m_UggWrongComp()
	, m_GraphicsComp(graphicsComp)
	, m_CubesWidth(cubesWidth)
	, m_CubesHeight(cubesHeight)
	, m_Jumping(false)
	, m_JumpingSpeed(300.f)
	, m_LiftoffPosX()
	, m_LiftoffPosY()
	, m_LandingPosX()
	, m_LandingPosY()
	, m_MidFlightPosX()
	, m_MidFlightPosY()
	, m_MovingRight()
	, m_MovingDown()
	, m_MovementXIncomplete()
	, m_MovementYIncomplete()
{}

JumpingObserver::JumpingObserver(UggWrongway* uggWrongComp, dae::GraphicsComponent* graphicsComp, float cubesWidth, float cubesHeight)
	: m_QBertComp()
	, m_CoilyComp()
	, m_SlickSamComp()
	, m_UggWrongComp(uggWrongComp)
	, m_GraphicsComp(graphicsComp)
	, m_CubesWidth(cubesWidth)
	, m_CubesHeight(cubesHeight)
	, m_Jumping(false)
	, m_JumpingSpeed(300.f)
	, m_LiftoffPosX()
	, m_LiftoffPosY()
	, m_LandingPosX()
	, m_LandingPosY()
	, m_MidFlightPosX()
	, m_MidFlightPosY()
	, m_MovingRight()
	, m_MovingDown()
	, m_MovementXIncomplete()
	, m_MovementYIncomplete()
{}

JumpingObserver::~JumpingObserver()
{
	if (m_QBertComp != nullptr)
		m_QBertComp->GetSubject()->RemoveObserver(this);

	if (m_CoilyComp != nullptr)
		m_CoilyComp->GetSubject()->RemoveObserver(this);

	if (m_SlickSamComp != nullptr)
		m_SlickSamComp->GetSubject()->RemoveObserver(this);

	if (m_UggWrongComp != nullptr)
		m_UggWrongComp->GetSubject()->RemoveObserver(this);

	m_GraphicsComp = nullptr;
}

void JumpingObserver::Initialize()
{
	if (m_QBertComp != nullptr)
		m_QBertComp->GetSubject()->AddObserver(this);
	
	if (m_CoilyComp != nullptr)
		m_CoilyComp->GetSubject()->AddObserver(this);

	if (m_SlickSamComp != nullptr)
		m_SlickSamComp->GetSubject()->AddObserver(this);

	if (m_UggWrongComp != nullptr)
		m_UggWrongComp->GetSubject()->AddObserver(this);
}

void JumpingObserver::SetQBert(QBert* qBertComp)
{
	if (m_QBertComp != nullptr)
		m_QBertComp->GetSubject()->RemoveObserver(this);

	m_QBertComp = qBertComp;

	if (m_QBertComp != nullptr)
		m_QBertComp->GetSubject()->AddObserver(this);
}

void JumpingObserver::SetCoily(Coily* coilyComp)
{
	if (m_CoilyComp != nullptr)
		m_CoilyComp->GetSubject()->RemoveObserver(this);

	m_CoilyComp = coilyComp;

	if (m_CoilyComp != nullptr)
		m_CoilyComp->GetSubject()->AddObserver(this);
}

void JumpingObserver::SetSlickSam(SlickSam* slickSamComp)
{
	if (m_SlickSamComp != nullptr)
		m_SlickSamComp->GetSubject()->RemoveObserver(this);

	m_SlickSamComp = slickSamComp;

	if (m_SlickSamComp != nullptr)
		m_SlickSamComp->GetSubject()->AddObserver(this);
}

void JumpingObserver::SetUggWrongway(UggWrongway* uggWrongComp)
{
	if (m_UggWrongComp != nullptr)
		m_UggWrongComp->GetSubject()->RemoveObserver(this);

	m_UggWrongComp = uggWrongComp;

	if (m_UggWrongComp != nullptr)
		m_UggWrongComp->GetSubject()->AddObserver(this);
}

void JumpingObserver::SetGraphics(dae::GraphicsComponent* graphicsComp)
{
	m_GraphicsComp = graphicsComp;
}

void JumpingObserver::OnNotify(const dae::Event& event)
{
	switch (event)
	{
	case dae::Event::JumpUpRight:
		m_LiftoffPosX = m_GraphicsComp->GetPosX();
		m_LiftoffPosY = m_GraphicsComp->GetPosY();
		m_MidFlightPosX = m_LiftoffPosX;
		m_MidFlightPosY = m_LiftoffPosY;
		m_LandingPosX = m_LiftoffPosX + m_CubesWidth / 2.f;
		m_LandingPosY = m_LiftoffPosY - m_CubesHeight * 0.75f;
		m_MovementXIncomplete = true;
		m_MovementYIncomplete = true;
		m_MovingRight = true;
		m_MovingDown = false;
		m_Jumping = true;
		break;


	case dae::Event::JumpUpLeft:
		m_LiftoffPosX = m_GraphicsComp->GetPosX();
		m_LiftoffPosY = m_GraphicsComp->GetPosY();
		m_MidFlightPosX = m_LiftoffPosX;
		m_MidFlightPosY = m_LiftoffPosY;
		m_LandingPosX = m_LiftoffPosX - m_CubesWidth / 2.f;
		m_LandingPosY = m_LiftoffPosY - m_CubesHeight * 0.75f;
		m_MovementXIncomplete = true;
		m_MovementYIncomplete = true;
		m_MovingRight = false;
		m_MovingDown = false;
		m_Jumping = true;
		break;


	case dae::Event::JumpDownRight:
		m_LiftoffPosX = m_GraphicsComp->GetPosX();
		m_LiftoffPosY = m_GraphicsComp->GetPosY();
		m_MidFlightPosX = m_LiftoffPosX;
		m_MidFlightPosY = m_LiftoffPosY;
		m_LandingPosX = m_LiftoffPosX + m_CubesWidth / 2.f;
		m_LandingPosY = m_LiftoffPosY + m_CubesHeight * 0.75f;
		m_MovementXIncomplete = true;
		m_MovementYIncomplete = true;
		m_MovingRight = true;
		m_MovingDown = true;
		m_Jumping = true;
		break;


	case dae::Event::JumpDownLeft:
		m_LiftoffPosX = m_GraphicsComp->GetPosX();
		m_LiftoffPosY = m_GraphicsComp->GetPosY();
		m_MidFlightPosX = m_LiftoffPosX;
		m_MidFlightPosY = m_LiftoffPosY;
		m_LandingPosX = m_LiftoffPosX - m_CubesWidth / 2.f;
		m_LandingPosY = m_LiftoffPosY + m_CubesHeight * 0.75f;
		m_MovementXIncomplete = true;
		m_MovementYIncomplete = true;
		m_MovingRight = false;
		m_MovingDown = true;
		m_Jumping = true;
		break;


	case dae::Event::JumpLeft:
		m_LiftoffPosX = m_GraphicsComp->GetPosX();
		m_LiftoffPosY = m_GraphicsComp->GetPosY();
		m_MidFlightPosX = m_LiftoffPosX;
		m_MidFlightPosY = m_LiftoffPosY;
		m_LandingPosX = m_LiftoffPosX - m_CubesWidth;
		m_LandingPosY = m_LiftoffPosY;
		m_MovementXIncomplete = true;
		m_MovingRight = false;
		m_Jumping = true;
		break;

		
	case dae::Event::JumpRight:
		m_LiftoffPosX = m_GraphicsComp->GetPosX();
		m_LiftoffPosY = m_GraphicsComp->GetPosY();
		m_MidFlightPosX = m_LiftoffPosX;
		m_MidFlightPosY = m_LiftoffPosY;
		m_LandingPosX = m_LiftoffPosX + m_CubesWidth;
		m_LandingPosY = m_LiftoffPosY;
		m_MovementXIncomplete = true;
		m_MovingRight = true;
		m_Jumping = true;
		break;
	}
}

void JumpingObserver::Update(const float deltaTime)
{
	if(m_Jumping)
	{
		// Movement in the X-Axis
		if (m_MovementXIncomplete)
		{
			if (m_MovingRight)
			{
				if (m_MidFlightPosX < m_LandingPosX)
					m_MidFlightPosX += m_JumpingSpeed * deltaTime;
				else
				{
					m_MidFlightPosX = m_LandingPosX;
					m_MovementXIncomplete = false;
				}
			}
			else
			{
				if (m_MidFlightPosX > m_LandingPosX)
					m_MidFlightPosX -= m_JumpingSpeed * deltaTime;
				else
				{
					m_MidFlightPosX = m_LandingPosX;
					m_MovementXIncomplete = false;
				}
			}
		}


		// Movement in the Y-Axis
		if (m_MovementYIncomplete)
		{
			if (m_MovingDown)
			{
				if (m_MidFlightPosY < m_LandingPosY)
					m_MidFlightPosY += m_JumpingSpeed * deltaTime;
				else
				{
					m_MidFlightPosY = m_LandingPosY;
					m_MovementYIncomplete = false;
				}
			}
			else
			{
				if (m_MidFlightPosY > m_LandingPosY)
					m_MidFlightPosY -= m_JumpingSpeed * deltaTime;
				else
				{
					m_MidFlightPosY = m_LandingPosY;
					m_MovementYIncomplete = false;
				}
			}
		}

		
		// Actually move the graphics
		m_GraphicsComp->SetPosition(m_MidFlightPosX, m_MidFlightPosY);



		// Stop the animation if the movement is complete
		if (m_MovementXIncomplete == false && m_MovementYIncomplete == false)
		{
			m_Jumping = false;
			
			if (m_QBertComp != nullptr)
				m_QBertComp->JumpFinished();
			else if (m_CoilyComp != nullptr)
				m_CoilyComp->JumpFinished();
			else if (m_SlickSamComp != nullptr)
				m_SlickSamComp->JumpFinished();
			else if (m_UggWrongComp != nullptr)
				m_UggWrongComp->JumpFinished();
		}
	}
}







