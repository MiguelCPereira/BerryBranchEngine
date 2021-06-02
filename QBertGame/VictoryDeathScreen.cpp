#include "VictoryDeathScreen.h"
#include "GameCommands.h"
#include "SceneManager.h"
#include "Scene.h"

VictoryDeathScreen::VictoryDeathScreen(int startMenuSceneIdx)
	: m_StartMenuSceneIdx(startMenuSceneIdx)
{
}

void VictoryDeathScreen::Update(const float)
{
}

void VictoryDeathScreen::GoBack() const
{
	auto& scene = dae::SceneManager::GetInstance();
	scene.ChangeScene(m_StartMenuSceneIdx);
}



