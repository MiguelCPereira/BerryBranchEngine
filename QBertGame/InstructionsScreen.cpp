#include "InstructionsScreen.h"
#include "GameCommands.h"
#include "SceneManager.h"
#include "Scene.h"

void InstructionsScreen::Update(const float)
{
}

void InstructionsScreen::ChangeScene() const
{
	auto& scene = dae::SceneManager::GetInstance();
	scene.ChangeScene(scene.GetCurrentSceneIdx() + 1);
}
