#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "TextComponent.h"
#include "GameObject.h"

dae::FPSComponent::FPSComponent(std::shared_ptr<GameObject> ownerObject)
	: m_GameObject(ownerObject)
{
}

void dae::FPSComponent::Initialize()
{
	m_Text = m_GameObject->GetComponent<TextComponent>();
}

void dae::FPSComponent::Update(const float deltaTime)
{
	m_SecCounter += deltaTime;

	m_FpsSumOverSec += 1.f / deltaTime;
	m_Frames++;

	if (m_SecCounter >= m_RenderInterval)
	{
		const int averageFps = int(m_FpsSumOverSec / m_Frames);
		m_FpsSumOverSec = 0.f;
		m_Frames = 0;
		std::string string = std::to_string(averageFps);
		string.append(" FPS");
		m_Text->SetText(string);

		m_SecCounter -= m_RenderInterval;
	}
}
