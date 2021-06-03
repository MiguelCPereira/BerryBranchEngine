#include "StartScreen.h"
#include <iostream>
#include "GraphicsComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "SoundServiceLocator.h"
#include "SoundSystem.h"


StartScreen::StartScreen(int soloModeSceneIdx, int coopModeSceneIdx, int versusModeSceneIdx, dae::GraphicsComponent* selectionGraphics, float buttonDistance)
	: m_SelectionGraphics(selectionGraphics)
	, m_ButtonDistance(buttonDistance)
	, m_Selection(0)
	, m_SoloModeSceneIdx(soloModeSceneIdx)
	, m_CoopModeSceneIdx(coopModeSceneIdx)
	, m_VersusModeSceneIdx(versusModeSceneIdx)
{
}

void StartScreen::ChangeSelection(bool up)
{
	if(up)
	{
		if (m_Selection - 1 < 0)
		{
			m_SelectionGraphics->SetPosition(m_SelectionGraphics->GetPosX(), m_SelectionGraphics->GetPosY() + m_ButtonDistance * 2.f);
			m_Selection = 2;
		}
		else
		{
			m_SelectionGraphics->SetPosition(m_SelectionGraphics->GetPosX(), m_SelectionGraphics->GetPosY() - m_ButtonDistance);
			m_Selection--;
		}
	}
	else
	{
		if (m_Selection + 1 > 2)
		{
			m_SelectionGraphics->SetPosition(m_SelectionGraphics->GetPosX(), m_SelectionGraphics->GetPosY() - m_ButtonDistance * 2.f);
			m_Selection = 0;
		}
		else
		{
			m_SelectionGraphics->SetPosition(m_SelectionGraphics->GetPosX(), m_SelectionGraphics->GetPosY() + m_ButtonDistance);
			m_Selection++;
		}
	}

	SoundServiceLocator::GetSoundSystem().Play("../Data/Sounds/Change Selection.wav", 0.3f);
}

void StartScreen::StartGame() const
{
	auto& scene = dae::SceneManager::GetInstance();


	switch (m_Selection)
	{
	case 0:
		scene.ChangeScene(m_SoloModeSceneIdx);
		break;
	case 1:
		scene.ChangeScene(m_CoopModeSceneIdx);
		break;
	case 2:
		scene.ChangeScene(m_VersusModeSceneIdx);
		break;
	default:
		std::cout << "Something went wrong, no game mode is selected\n";
	}
}


void StartScreen::Update(const float)
{
}


