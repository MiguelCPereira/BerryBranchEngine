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
	//scene.ChangeScene(0); // NEED TO UNCOMMENT FOR DEBUGGING
	scene.ChangeScene(scene.GetCurrentSceneIdx() + 1); // NEED TO UNCOMMENT For DEBUGGING
}
