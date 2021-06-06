#include "InstructionsScreen.h"
#include "SceneManager.h"
#include "InputManager.h"

void InstructionsScreen::Update(const float)
{
}

void InstructionsScreen::ChangeScene() const
{
	dae::InputManager::GetInstance().ClearAllCommands();
	auto& scene = dae::SceneManager::GetInstance();
	scene.ChangeScene(scene.GetCurrentSceneIdx() + 1);
}
