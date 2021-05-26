// Project includes
#define SDL_MAIN_HANDLED
#include <Minigin.h>
#include <memory>
#include<string>
#include <cstdlib>
#include <ctime>
#include "Pyramid.h"
#include "Factory.h"
#include "Scene.h"
#include "GameObject.h"
#include "Command.h"
#include "InputManager.h"
#include "GameCommands.h"
#include "LevelSectionObserver.h"


// Global Variables
const int g_CubesSpriteHeight = 32;
const int g_CubesSpriteWidth = 32;
std::vector<std::shared_ptr<dae::GameObject>> g_QBertGOs;


// Global Functions
void SetUpGlobalGOs();
void LoadLevel01();
void LoadLevel02();
void LoadLevel03();
void LoadLevel04();
void PrintInstructions();




int main(int, char* [])
{
	srand((unsigned)time(nullptr));

    dae::Minigin engine;
    engine.Initialize();

	SetUpGlobalGOs();
	LoadLevel01();
	LoadLevel02();
	LoadLevel03();
	PrintInstructions();
	
	engine.Run();
	
    return 0;
}




void LoadLevel01()
{
	//// Level Title Screen

	// Create Scene
	auto& levelTitleScene = dae::SceneManager::GetInstance().CreateScene("Level01Title");

	// Add All Needed Game Objects
	levelTitleScene.Add(MakeLevelTitle(1));
	levelTitleScene.Add(MakeLevelTransition(g_QBertGOs[0]->GetComponent<QBert>()));

	// Initialize Scene
	levelTitleScene.Initialize();
	
	
	
	//// Section 01

	// Create Scene
	auto& scene1 = dae::SceneManager::GetInstance().CreateScene("Level01A");

	// Level Map
	auto* pyramid = new Pyramid(300.f, 80.f, g_NrRows, g_CubesActualWidth, g_CubesActualHeight,
		0, 1, g_CubesSpriteWidth, g_CubesSpriteHeight);
	for (const std::shared_ptr<dae::GameObject>& cube : pyramid->m_CubeGOVector)
		scene1.Add(cube);

	// Transfer QBert
	for(auto gameObject : g_QBertGOs)
		scene1.Add(gameObject);

	// Make Level/Round Display
	scene1.Add(MakeRoundLevelDisplayGO(g_QBertGOs[0]->GetComponent<QBert>(), false));
	
	// Level Section Observer
	auto sectionObserverGO = std::make_shared<dae::GameObject>();
	sectionObserverGO->AddComponent(new LevelSectionObserver(sectionObserverGO, g_QBertGOs[0]->GetComponent<QBert>(),
		pyramid, 1, false, false));
	
	scene1.Add(sectionObserverGO);

	// FPS Counter
	scene1.Add(MakeFPSCounter());

	
	//////////////////////////


	//// Section 02
	
	// Create Scene
	auto& scene2 = dae::SceneManager::GetInstance().CreateScene("Level01B");

	// Level Map
	pyramid = new Pyramid(300.f, 80.f, g_NrRows, g_CubesActualWidth, g_CubesActualHeight,
		1, 1, g_CubesSpriteWidth, g_CubesSpriteHeight);
	for (const std::shared_ptr<dae::GameObject>& cube : pyramid->m_CubeGOVector)
		scene2.Add(cube);

	// Transfer QBert
	for (auto gameObject : g_QBertGOs)
		scene2.Add(gameObject);

	// Make Level/Round Display
	scene2.Add(MakeRoundLevelDisplayGO(g_QBertGOs[0]->GetComponent<QBert>(), false));

	// Level Section Observer
	sectionObserverGO = std::make_shared<dae::GameObject>();
	sectionObserverGO->AddComponent(new LevelSectionObserver(sectionObserverGO, g_QBertGOs[0]->GetComponent<QBert>(),
		pyramid, 1, false, false));
	scene2.Add(sectionObserverGO);

	// FPS Counter
	scene2.Add(MakeFPSCounter());


	//////////////////////////


	//// Section 03
	
	// Create Scene
	auto& scene3 = dae::SceneManager::GetInstance().CreateScene("Level01C");

	// Level Map
	pyramid = new Pyramid(300.f, 80.f, g_NrRows, g_CubesActualWidth, g_CubesActualHeight,
		2, 1, g_CubesSpriteWidth, g_CubesSpriteHeight);
	for (const std::shared_ptr<dae::GameObject>& cube : pyramid->m_CubeGOVector)
		scene3.Add(cube);

	// Transfer QBert
	for (auto gameObject : g_QBertGOs)
		scene3.Add(gameObject);

	// Make Level/Round Display
	scene3.Add(MakeRoundLevelDisplayGO(g_QBertGOs[0]->GetComponent<QBert>(), false));

	// Level Section Observer
	sectionObserverGO = std::make_shared<dae::GameObject>();
	sectionObserverGO->AddComponent(new LevelSectionObserver(sectionObserverGO, g_QBertGOs[0]->GetComponent<QBert>(),
		pyramid, 1, false, true, 0, 10.f));
	scene3.Add(sectionObserverGO);

	// FPS Counter
	scene3.Add(MakeFPSCounter());

	//////////////////////////


	//// Section 04
	
	// Create Scene
	auto& scene4 = dae::SceneManager::GetInstance().CreateScene("Level01D");

	// Level Map
	pyramid = new Pyramid(300.f, 80.f, g_NrRows, g_CubesActualWidth, g_CubesActualHeight,
		3, 1, g_CubesSpriteWidth, g_CubesSpriteHeight);
	for (const std::shared_ptr<dae::GameObject>& cube : pyramid->m_CubeGOVector)
		scene4.Add(cube);

	// Transfer QBert
	for (auto gameObject : g_QBertGOs)
		scene4.Add(gameObject);

	// Make Level/Round Display
	scene4.Add(MakeRoundLevelDisplayGO(g_QBertGOs[0]->GetComponent<QBert>(), false));

	// Level Section Observer
	sectionObserverGO = std::make_shared<dae::GameObject>();
	sectionObserverGO->AddComponent(new LevelSectionObserver(sectionObserverGO, g_QBertGOs[0]->GetComponent<QBert>(),
		pyramid, 1, false, true, 0, 7.f));
	scene4.Add(sectionObserverGO);

	// FPS Counter
	scene4.Add(MakeFPSCounter());
}

void LoadLevel02()
{
	//// Level Title Screen

	// Create Scene
	auto& levelTitleScene = dae::SceneManager::GetInstance().CreateScene("Level01Title");

	// Add All Needed Game Objects
	levelTitleScene.Add(MakeLevelTitle(2));
	levelTitleScene.Add(MakeLevelTransition(g_QBertGOs[0]->GetComponent<QBert>()));



	//// Section 01

	// Create Scene
	auto& scene1 = dae::SceneManager::GetInstance().CreateScene("Level02A");

	// Level Map
	auto* pyramid = new Pyramid(300.f, 80.f, g_NrRows, g_CubesActualWidth, g_CubesActualHeight,
		1, 2, g_CubesSpriteWidth, g_CubesSpriteHeight);
	for (const std::shared_ptr<dae::GameObject>& cube : pyramid->m_CubeGOVector)
		scene1.Add(cube);

	// Transfer QBert
	for (auto gameObject : g_QBertGOs)
		scene1.Add(gameObject);

	// Make Level/Round Display
	scene1.Add(MakeRoundLevelDisplayGO(g_QBertGOs[0]->GetComponent<QBert>(), false));

	// Level Section Observer
	auto sectionObserverGO = std::make_shared<dae::GameObject>();
	sectionObserverGO->AddComponent(new LevelSectionObserver(sectionObserverGO, g_QBertGOs[0]->GetComponent<QBert>(),
		pyramid, 2, true, true, 20.f, 15.f));
	scene1.Add(sectionObserverGO);

	// FPS Counter
	scene1.Add(MakeFPSCounter());


	//////////////////////////


	//// Section 02

	// Create Scene
	auto& scene2 = dae::SceneManager::GetInstance().CreateScene("Level02B");

	// Level Map
	pyramid = new Pyramid(300.f, 80.f, g_NrRows, g_CubesActualWidth, g_CubesActualHeight,
		3, 2, g_CubesSpriteWidth, g_CubesSpriteHeight);
	for (const std::shared_ptr<dae::GameObject>& cube : pyramid->m_CubeGOVector)
		scene2.Add(cube);

	// Transfer QBert
	for (auto gameObject : g_QBertGOs)
		scene2.Add(gameObject);

	// Make Level/Round Display
	scene2.Add(MakeRoundLevelDisplayGO(g_QBertGOs[0]->GetComponent<QBert>(), false));

	// Level Section Observer
	sectionObserverGO = std::make_shared<dae::GameObject>();
	sectionObserverGO->AddComponent(new LevelSectionObserver(sectionObserverGO, g_QBertGOs[0]->GetComponent<QBert>(),
		pyramid, 2, true, true, 15.f, 10.f));
	scene2.Add(sectionObserverGO);

	// FPS Counter
	scene2.Add(MakeFPSCounter());


	//////////////////////////


	//// Section 03

	// Create Scene
	auto& scene3 = dae::SceneManager::GetInstance().CreateScene("Level02C");

	// Level Map
	pyramid = new Pyramid(300.f, 80.f, g_NrRows, g_CubesActualWidth, g_CubesActualHeight,
		0, 2, g_CubesSpriteWidth, g_CubesSpriteHeight);
	for (const std::shared_ptr<dae::GameObject>& cube : pyramid->m_CubeGOVector)
		scene3.Add(cube);

	// Transfer QBert
	for (auto gameObject : g_QBertGOs)
		scene3.Add(gameObject);

	// Make Level/Round Display
	scene3.Add(MakeRoundLevelDisplayGO(g_QBertGOs[0]->GetComponent<QBert>(), false));

	// Level Section Observer
	sectionObserverGO = std::make_shared<dae::GameObject>();
	sectionObserverGO->AddComponent(new LevelSectionObserver(sectionObserverGO, g_QBertGOs[0]->GetComponent<QBert>(),
		pyramid, 2, true, true, 10.f, 7.f));
	scene3.Add(sectionObserverGO);

	// FPS Counter
	scene3.Add(MakeFPSCounter());


	//////////////////////////


	//// Section 04

	// Create Scene
	auto& scene4 = dae::SceneManager::GetInstance().CreateScene("Level02D");

	// Level Map
	pyramid = new Pyramid(300.f, 80.f, g_NrRows, g_CubesActualWidth, g_CubesActualHeight,
		4, 2, g_CubesSpriteWidth, g_CubesSpriteHeight);
	for (const std::shared_ptr<dae::GameObject>& cube : pyramid->m_CubeGOVector)
		scene4.Add(cube);

	// Transfer QBert
	for (auto gameObject : g_QBertGOs)
		scene4.Add(gameObject);

	// Make Level/Round Display
	scene4.Add(MakeRoundLevelDisplayGO(g_QBertGOs[0]->GetComponent<QBert>(), false));

	// Level Section Observer
	sectionObserverGO = std::make_shared<dae::GameObject>();
	sectionObserverGO->AddComponent(new LevelSectionObserver(sectionObserverGO, g_QBertGOs[0]->GetComponent<QBert>(),
		pyramid, 2, true, true, 5.f, 5.f));
	scene4.Add(sectionObserverGO);

	// FPS Counter
	scene4.Add(MakeFPSCounter());
}

void LoadLevel03()
{
	//// Level Title Screen

	// Create Scene
	auto& levelTitleScene = dae::SceneManager::GetInstance().CreateScene("Level01Title");

	// Add All Needed Game Objects
	levelTitleScene.Add(MakeLevelTitle(3));
	levelTitleScene.Add(MakeLevelTransition(g_QBertGOs[0]->GetComponent<QBert>()));



	//// Section 01

	// Create Scene
	auto& scene1 = dae::SceneManager::GetInstance().CreateScene("Level03A");

	// Level Map
	auto* pyramid = new Pyramid(300.f, 80.f, g_NrRows, g_CubesActualWidth, g_CubesActualHeight,
		5, 3, g_CubesSpriteWidth, g_CubesSpriteHeight);
	for (const std::shared_ptr<dae::GameObject>& cube : pyramid->m_CubeGOVector)
		scene1.Add(cube);

	// Transfer QBert
	for (auto gameObject : g_QBertGOs)
		scene1.Add(gameObject);

	// Make Level/Round Display
	scene1.Add(MakeRoundLevelDisplayGO(g_QBertGOs[0]->GetComponent<QBert>(), false));

	// Level Section Observer
	auto sectionObserverGO = std::make_shared<dae::GameObject>();
	sectionObserverGO->AddComponent(new LevelSectionObserver(sectionObserverGO, g_QBertGOs[0]->GetComponent<QBert>(),
		pyramid, 3, true, true, 25.f, 15.f));
	scene1.Add(sectionObserverGO);

	// FPS Counter
	scene1.Add(MakeFPSCounter());


	//////////////////////////


	//// Section 02

	// Create Scene
	auto& scene2 = dae::SceneManager::GetInstance().CreateScene("Level02B");

	// Level Map
	pyramid = new Pyramid(300.f, 80.f, g_NrRows, g_CubesActualWidth, g_CubesActualHeight,
		2, 3, g_CubesSpriteWidth, g_CubesSpriteHeight);
	for (const std::shared_ptr<dae::GameObject>& cube : pyramid->m_CubeGOVector)
		scene2.Add(cube);

	// Transfer QBert
	for (auto gameObject : g_QBertGOs)
		scene2.Add(gameObject);

	// Make Level/Round Display
	scene2.Add(MakeRoundLevelDisplayGO(g_QBertGOs[0]->GetComponent<QBert>(), false));

	// Level Section Observer
	sectionObserverGO = std::make_shared<dae::GameObject>();
	sectionObserverGO->AddComponent(new LevelSectionObserver(sectionObserverGO, g_QBertGOs[0]->GetComponent<QBert>(),
		pyramid, 3, true, true, 20.f, 10.f));
	scene2.Add(sectionObserverGO);

	// FPS Counter
	scene2.Add(MakeFPSCounter());


	//////////////////////////


	//// Section 03

	// Create Scene
	auto& scene3 = dae::SceneManager::GetInstance().CreateScene("Level02C");

	// Level Map
	pyramid = new Pyramid(300.f, 80.f, g_NrRows, g_CubesActualWidth, g_CubesActualHeight,
		1, 3, g_CubesSpriteWidth, g_CubesSpriteHeight);
	for (const std::shared_ptr<dae::GameObject>& cube : pyramid->m_CubeGOVector)
		scene3.Add(cube);

	// Transfer QBert
	for (auto gameObject : g_QBertGOs)
		scene3.Add(gameObject);

	// Make Level/Round Display
	scene3.Add(MakeRoundLevelDisplayGO(g_QBertGOs[0]->GetComponent<QBert>(), false));

	// Level Section Observer
	sectionObserverGO = std::make_shared<dae::GameObject>();
	sectionObserverGO->AddComponent(new LevelSectionObserver(sectionObserverGO, g_QBertGOs[0]->GetComponent<QBert>(),
		pyramid, 3, true, true, 15.f, 7.f));
	scene3.Add(sectionObserverGO);

	// FPS Counter
	scene3.Add(MakeFPSCounter());


	//////////////////////////


	//// Section 04

	// Create Scene
	auto& scene4 = dae::SceneManager::GetInstance().CreateScene("Level02D");

	// Level Map
	pyramid = new Pyramid(300.f, 80.f, g_NrRows, g_CubesActualWidth, g_CubesActualHeight,
		0, 3, g_CubesSpriteWidth, g_CubesSpriteHeight);
	for (const std::shared_ptr<dae::GameObject>& cube : pyramid->m_CubeGOVector)
		scene4.Add(cube);

	// Transfer QBert
	for (auto gameObject : g_QBertGOs)
		scene4.Add(gameObject);

	// Make Level/Round Display
	scene4.Add(MakeRoundLevelDisplayGO(g_QBertGOs[0]->GetComponent<QBert>(), false));

	// Level Section Observer
	sectionObserverGO = std::make_shared<dae::GameObject>();
	sectionObserverGO->AddComponent(new LevelSectionObserver(sectionObserverGO, g_QBertGOs[0]->GetComponent<QBert>(),
		pyramid, 3, true, true, 10.f, 5.f));
	scene4.Add(sectionObserverGO);

	// FPS Counter
	scene4.Add(MakeFPSCounter());





	//// Victory Screen

	// Create Scene
	auto& victoryScene = dae::SceneManager::GetInstance().CreateScene("VictoryScene");

	// Add All Needed Game Objects
	victoryScene.Add(MakeVictoryTitle());
}

void SetUpGlobalGOs()
{
	// QBert
	g_QBertGOs = MakeQBert();
	
	 
	// Player Input
	auto moveUpKeyboard = std::make_unique<QBertMoveUpCommand>();
	moveUpKeyboard->SetActor(g_QBertGOs[0]);
	moveUpKeyboard->SetButtonPressType(dae::ButtonPress::PressedDown);
	dae::InputManager::GetInstance().AddCommand(SDLK_w, std::move(moveUpKeyboard));

	auto moveDownKeyboard = std::make_unique<QBertMoveDownCommand>();
	moveDownKeyboard->SetActor(g_QBertGOs[0]);
	moveDownKeyboard->SetButtonPressType(dae::ButtonPress::PressedDown);
	dae::InputManager::GetInstance().AddCommand(SDLK_s, std::move(moveDownKeyboard));

	auto moveLeftKeyboard = std::make_unique<QBertMoveLeftCommand>();
	moveLeftKeyboard->SetActor(g_QBertGOs[0]);
	moveLeftKeyboard->SetButtonPressType(dae::ButtonPress::PressedDown);
	dae::InputManager::GetInstance().AddCommand(SDLK_a, std::move(moveLeftKeyboard));

	auto moveRightKeyboard = std::make_unique<QBertMoveRightCommand>();
	moveRightKeyboard->SetActor(g_QBertGOs[0]);
	moveRightKeyboard->SetButtonPressType(dae::ButtonPress::PressedDown);
	dae::InputManager::GetInstance().AddCommand(SDLK_d, std::move(moveRightKeyboard));

	auto moveUpController = std::make_unique<QBertMoveUpCommand>();
	moveUpController->SetActor(g_QBertGOs[0]);
	moveUpController->SetButtonPressType(dae::ButtonPress::PressedDown);
	std::pair<unsigned, dae::ControllerButton> controllerKey(0, dae::ControllerButton::DPadUp);
	dae::InputManager::GetInstance().AddCommand(controllerKey, std::move(moveUpController));

	auto moveDownController = std::make_unique<QBertMoveDownCommand>();
	moveDownController->SetActor(g_QBertGOs[0]);
	moveDownController->SetButtonPressType(dae::ButtonPress::PressedDown);
	controllerKey.second = dae::ControllerButton::DPadDown;
	dae::InputManager::GetInstance().AddCommand(controllerKey, std::move(moveDownController));

	auto moveLeftController = std::make_unique<QBertMoveLeftCommand>();
	moveLeftController->SetActor(g_QBertGOs[0]);
	moveLeftController->SetButtonPressType(dae::ButtonPress::PressedDown);
	controllerKey.second = dae::ControllerButton::DPadLeft;
	dae::InputManager::GetInstance().AddCommand(controllerKey, std::move(moveLeftController));

	auto moveRightController = std::make_unique<QBertMoveRightCommand>();
	moveRightController->SetActor(g_QBertGOs[0]);
	moveRightController->SetButtonPressType(dae::ButtonPress::PressedDown);
	controllerKey.second = dae::ControllerButton::DPadRight;
	dae::InputManager::GetInstance().AddCommand(controllerKey, std::move(moveRightController));


	// Game Observer
	//auto gameObjectGO = std::make_shared<dae::GameObject>();
	//g_GameObserverGO = std::move(gameObjectGO);
}

void PrintInstructions()
{
	std::cout << "Controls:\n";
	std::cout << "\n";
	std::cout << "   W or DPad Up     | Move Up/Right\n";
	std::cout << "   A or DPad Left   | Move Up/Left\n";
	std::cout << "   S or DPad Down   | Move Down/Left\n";
	std::cout << "   D or DPad Right  | Move Down/Right\n\n";
}