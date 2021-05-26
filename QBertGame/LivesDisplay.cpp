#include "LivesDisplay.h"
#include "GameObject.h"
#include "QBert.h"
#include "GraphicsComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Factory.h"

LivesDisplay::LivesDisplay(QBert* qBertComp)
	: m_QBertComp(qBertComp)
	, m_Graphics()
{
	m_Graphics = new std::vector<dae::GraphicsComponent*>;
}

LivesDisplay::~LivesDisplay()
{
	if (m_QBertComp != nullptr)
		m_QBertComp->GetSubject()->RemoveObserver(this);

	delete m_Graphics;
	m_Graphics = nullptr;
}



void LivesDisplay::Initialize()
{
	if (m_QBertComp != nullptr)
	{
		m_QBertComp->GetSubject()->AddObserver(this);
		m_QBertComp->SetFrozen(false);
	}

	m_Graphics->clear();

	auto posY = 130.f;
	for (auto i = 0; i < m_QBertComp->GetCurrentLives(); i++)
	{
		auto heartGO = MakeHeartForDisplay(true, posY);
		posY += 40.f;
		m_Graphics->push_back(heartGO->GetComponent<dae::GraphicsComponent>());
		dae::SceneManager::GetInstance().GetCurrentScene()->Add(heartGO);
	}
}


void LivesDisplay::SetQBert(QBert* qBertComp)
{
	if (m_QBertComp != nullptr)
		m_QBertComp->GetSubject()->RemoveObserver(this);

	m_QBertComp = qBertComp;

	if (m_QBertComp != nullptr)
		m_QBertComp->GetSubject()->AddObserver(this);
}


void LivesDisplay::OnNotify(const dae::Event& event)
{
	switch (event)
	{
	case dae::Event::QBertDied:
		if(m_QBertComp->GetCurrentLives() >= 0)
			m_Graphics->operator[](m_QBertComp->GetCurrentLives())->SetPosition(-50, -50);
		break;
	}
}

void LivesDisplay::Update(const float)
{
}

