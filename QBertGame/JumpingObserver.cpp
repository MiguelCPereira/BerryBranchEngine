#include "JumpingObserver.h"
#include "GraphicsComponent.h"
#include "QBert.h"

JumpingObserver::JumpingObserver(const std::shared_ptr<dae::GameObject>& gameObject, QBert* qBertComp,
			dae::GraphicsComponent* graphicsComp, float cubesWidth, float cubesHeight)
	: m_GameObject(gameObject)
	, m_QBertComp(qBertComp)
	, m_GraphicsComp(graphicsComp)
	, m_CubesWidth(cubesWidth)
	, m_CubesHeight(cubesHeight)
{}

JumpingObserver::~JumpingObserver()
{
	if (m_QBertComp != nullptr)
		m_QBertComp->GetSubject()->RemoveObserver(this);

	m_GraphicsComp = nullptr;
}

void JumpingObserver::Initialize()
{
	if (m_QBertComp != nullptr)
		m_QBertComp->GetSubject()->AddObserver(this);
}

void JumpingObserver::SetQBert(QBert* qBertComp)
{
	if (m_QBertComp != nullptr)
		m_QBertComp->GetSubject()->RemoveObserver(this);

	m_QBertComp = qBertComp;

	if (m_QBertComp != nullptr)
		m_QBertComp->GetSubject()->AddObserver(this);
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
		m_GraphicsComp->SetPosition(m_GraphicsComp->GetPosX() + m_CubesWidth / 2.f, m_GraphicsComp->GetPosY() - m_CubesHeight * 0.75f);
		if (m_QBertComp != nullptr)
			m_QBertComp->JumpFinished();
		break;


	case dae::Event::JumpUpLeft:
		m_GraphicsComp->SetPosition(m_GraphicsComp->GetPosX() - m_CubesWidth / 2.f, m_GraphicsComp->GetPosY() - m_CubesHeight * 0.75f);
		if (m_QBertComp != nullptr)
			m_QBertComp->JumpFinished();
		break;


	case dae::Event::JumpDownRight:
		m_GraphicsComp->SetPosition(m_GraphicsComp->GetPosX() + m_CubesWidth / 2.f, m_GraphicsComp->GetPosY() + m_CubesHeight * 0.75f);
		if (m_QBertComp != nullptr)
			m_QBertComp->JumpFinished();
		break;


	case dae::Event::JumpDownLeft:
		m_GraphicsComp->SetPosition(m_GraphicsComp->GetPosX() - m_CubesWidth / 2.f, m_GraphicsComp->GetPosY() + m_CubesHeight * 0.75f);
		if (m_QBertComp != nullptr)
			m_QBertComp->JumpFinished();
		break;


	case dae::Event::JumpLeft:
		break;

		
	case dae::Event::JumpRight:
		break;
	}
}

void JumpingObserver::Update(const float)
{
	// Some animation ig
}







