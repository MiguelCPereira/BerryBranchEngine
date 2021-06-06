#include "LivesDisplay.h"
#include "QBert.h"
#include "GraphicsComponent.h"

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

		// Re-show all heart, in case they're hidden
		for (auto i = 0; i < int(m_Graphics->size()); i++)
		{
			auto* heart = m_Graphics->operator[](i);
			heart->SetHidden(false);
		}

		// Hide as many hearts as lives Qbert has lost
		const auto heartsToHide = int(m_Graphics->size()) - m_QBertComp->GetCurrentLives();
		for (auto i = 0; i < heartsToHide; i++)
		{
			auto* heart = m_Graphics->operator[](m_Graphics->size() - 1 - i);
			heart->SetHidden(true);
		}
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
	case dae::Event::QBertDiedP1:
		if(m_QBertComp->GetCurrentLives() >= 0)
		{
			auto* heart = m_Graphics->operator[](m_QBertComp->GetCurrentLives());
			heart->SetHidden(true);
		}
		break;

	case dae::Event::QBertDiedP2:
		if (m_QBertComp->GetCurrentLives() >= 0)
		{
			auto* heart = m_Graphics->operator[](m_QBertComp->GetCurrentLives());
			heart->SetHidden(true);
		}
		break;
	}
}

void LivesDisplay::Update(const float)
{
}

