#include "LivesDisplay.h"
#include "GameObject.h"
#include "QBert.h"
#include "GraphicsComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Factory.h"

LivesDisplay::LivesDisplay(QBert* qBertComp, std::vector<dae::GraphicsComponent*>* heartGraphics)
	: m_QBertComp(qBertComp)
	, m_Graphics(heartGraphics)
{
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

	const auto heartsToHide = int(m_Graphics->size()) - m_QBertComp->GetCurrentLives();

	for(auto i = 0; i < heartsToHide; i++)
		m_Graphics->operator[](m_Graphics->size() - 1 - i)->SetPosition(-50, -50);
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

