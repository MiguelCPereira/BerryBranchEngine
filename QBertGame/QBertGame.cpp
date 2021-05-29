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
#include "Disk.h"
#include "StartScreenInput.h"
#include "PlayerOneInput.h"
#include "VictoryDeathScreenInput.h"


// Global Variables
const int g_CubesSpriteHeight = 32;
const int g_CubesSpriteWidth = 32;
std::vector<std::shared_ptr<dae::GameObject>> g_QBertGOs;
auto* qBertsCompVector = new std::vector<QBert*>();


// Global Functions
void SetUpGlobalGOs();
void LoadDeathScreen();
void LoadStartScreen();
void LoadLevel01();
void LoadLevel02();
void LoadLevel03();
void LoadVictoryScreen();
void PrintInstructions();




int main(int, char* [])
{
	srand((unsigned)time(nullptr));

    dae::Minigin engine;
    engine.Initialize();

	//engine.LoadDemo();
	
	SetUpGlobalGOs();
	LoadStartScreen();
	LoadDeathScreen();
	LoadLevel01();
	LoadLevel02();
	LoadLevel03();
	LoadVictoryScreen();
	PrintInstructions();
	
	engine.Run();
	
    return 0;
}




void LoadStartScreen()
{
	// Create Scene
	auto& startScreenScene = dae::SceneManager::GetInstance().CreateScene("StartScreen");

	// Add All Needed Game Objects
	startScreenScene.Add(MakeStartScreenVisuals());
	const auto startScreenGO = MakeStartScreenLogic(2, 2, 2);
	startScreenScene.Add(startScreenGO);

	// Add The Start Menu Player Input
	auto menuPlayerInputGO = std::make_shared<dae::GameObject>();
	menuPlayerInputGO->AddComponent(new StartScreenInput(startScreenGO));
	startScreenScene.Add(menuPlayerInputGO);

	// Initialize Scene
	startScreenScene.Initialize();
}

void LoadDeathScreen()
{
	// Create Scene
	auto& deathScreenScene = dae::SceneManager::GetInstance().CreateScene("DeathScreen");

	// Add All Needed Game Objects
	deathScreenScene.Add(MakeDeathScreenVisuals());
	const auto deathScreenGO = MakeVictoryDeathScreenLogic(0, g_QBertGOs[0]->GetComponent<QBert>());
	deathScreenScene.Add(deathScreenGO);

	// Add The Victory/Death Screen Player Input
	auto deathScreenInputGO = std::make_shared<dae::GameObject>();
	deathScreenInputGO->AddComponent(new VictoryDeathScreenInput(deathScreenGO));
	deathScreenScene.Add(deathScreenInputGO);
}

void LoadLevel01()
{
	//// Level Title Screen

	// Create Scene
	auto& levelTitleScene = dae::SceneManager::GetInstance().CreateScene("Level01Title");

	// Add All Needed Game Objects
	levelTitleScene.Add(MakeLevelTitle(1));
	levelTitleScene.Add(MakeLevelTransition(g_QBertGOs[0]->GetComponent<QBert>()));
	
	
	
	//// Section 01

	// Create Scene
	auto& scene1 = dae::SceneManager::GetInstance().CreateScene("Level01A");

	// Level Map
	auto* pyramid = new Pyramid(300.f, 80.f, g_NrRows, g_CubesActualWidth, g_CubesActualHeight,
		0, 1, g_CubesSpriteWidth, g_CubesSpriteHeight);
	for (const std::shared_ptr<dae::GameObject>& cube : pyramid->m_CubeGOVector)
		scene1.Add(cube);

	// Disks
	auto* diskGOsVector = MakeDiskGOsVector(1, 0);
	auto* disksVector = new std::vector<Disk*>();
	for(size_t i = 0; i < diskGOsVector->size(); i++)
	{
		disksVector->push_back(diskGOsVector->operator[](i)->GetComponent<Disk>());
		scene1.Add(diskGOsVector->operator[](i));
	}
	
	// Transfer QBert
	for(const auto& gameObject : g_QBertGOs)
		scene1.Add(gameObject);

	// Make UI
	auto uiGOs = MakeUI(qBertsCompVector, false);
	for (const auto& gameObject : uiGOs)
		scene1.Add(gameObject);
	
	// Level Section Observer
	auto sectionObserverGO = std::make_shared<dae::GameObject>();
	sectionObserverGO->AddComponent(new LevelSectionObserver(sectionObserverGO, g_QBertGOs[0],
		pyramid, disksVector, 1, 1, false, false));
	
	scene1.Add(sectionObserverGO);

	// Add The Mode's Player Input
	auto gamePlayerInputGO = std::make_shared<dae::GameObject>();
	gamePlayerInputGO->AddComponent(new PlayerOneInput(g_QBertGOs[0]));
	scene1.Add(gamePlayerInputGO);

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

	// Disks
	diskGOsVector = MakeDiskGOsVector(1, 1);
	disksVector = new std::vector<Disk*>();
	for (size_t i = 0; i < diskGOsVector->size(); i++)
	{
		disksVector->push_back(diskGOsVector->operator[](i)->GetComponent<Disk>());
		scene2.Add(diskGOsVector->operator[](i));
	}
	
	// Transfer QBert
	for (const auto& gameObject : g_QBertGOs)
		scene2.Add(gameObject);

	// Make UI
	for (const auto& gameObject : uiGOs)
		scene2.Add(gameObject);

	// Level Section Observer
	sectionObserverGO = std::make_shared<dae::GameObject>();
	sectionObserverGO->AddComponent(new LevelSectionObserver(sectionObserverGO, g_QBertGOs[0],
		pyramid, disksVector, 1, 1, false, false));
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

	// Disks
	diskGOsVector = MakeDiskGOsVector(1, 2);
	disksVector = new std::vector<Disk*>();
	for (size_t i = 0; i < diskGOsVector->size(); i++)
	{
		disksVector->push_back(diskGOsVector->operator[](i)->GetComponent<Disk>());
		scene3.Add(diskGOsVector->operator[](i));
	}

	// Transfer QBert
	for (const auto& gameObject : g_QBertGOs)
		scene3.Add(gameObject);

	// Make UI
	for (const auto& gameObject : uiGOs)
		scene3.Add(gameObject);

	// Level Section Observer
	sectionObserverGO = std::make_shared<dae::GameObject>();
	sectionObserverGO->AddComponent(new LevelSectionObserver(sectionObserverGO, g_QBertGOs[0],
		pyramid, disksVector, 1, 1, false, true, 0, 10.f));
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

	// Disks
	diskGOsVector = MakeDiskGOsVector(1, 3);
	disksVector = new std::vector<Disk*>();
	for (size_t i = 0; i < diskGOsVector->size(); i++)
	{
		disksVector->push_back(diskGOsVector->operator[](i)->GetComponent<Disk>());
		scene4.Add(diskGOsVector->operator[](i));
	}
	
	// Transfer QBert
	for (const auto& gameObject : g_QBertGOs)
		scene4.Add(gameObject);

	// Make UI
	for (const auto& gameObject : uiGOs)
		scene4.Add(gameObject);

	// Level Section Observer
	sectionObserverGO = std::make_shared<dae::GameObject>();
	sectionObserverGO->AddComponent(new LevelSectionObserver(sectionObserverGO, g_QBertGOs[0],
		pyramid, disksVector, 1, 1, false, true, 0, 7.f));
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

	// Disks
	auto* diskGOsVector = MakeDiskGOsVector(2, 1);
	auto* disksVector = new std::vector<Disk*>();
	for (size_t i = 0; i < diskGOsVector->size(); i++)
	{
		disksVector->push_back(diskGOsVector->operator[](i)->GetComponent<Disk>());
		scene1.Add(diskGOsVector->operator[](i));
	}

	// Transfer QBert
	for (const auto& gameObject : g_QBertGOs)
		scene1.Add(gameObject);

	// Make UI
	auto uiGOs = MakeUI(qBertsCompVector, false);
	for (const auto& gameObject : uiGOs)
		scene1.Add(gameObject);

	// Level Section Observer
	auto sectionObserverGO = std::make_shared<dae::GameObject>();
	sectionObserverGO->AddComponent(new LevelSectionObserver(sectionObserverGO, g_QBertGOs[0],
		pyramid, disksVector, 1, 2, true, true, 20.f, 15.f));
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

	// Disks
	diskGOsVector = MakeDiskGOsVector(2, 3);
	disksVector = new std::vector<Disk*>();
	for (size_t i = 0; i < diskGOsVector->size(); i++)
	{
		disksVector->push_back(diskGOsVector->operator[](i)->GetComponent<Disk>());
		scene2.Add(diskGOsVector->operator[](i));
	}

	// Transfer QBert
	for (const auto& gameObject : g_QBertGOs)
		scene2.Add(gameObject);

	// Make UI
	for (const auto& gameObject : uiGOs)
		scene2.Add(gameObject);

	// Level Section Observer
	sectionObserverGO = std::make_shared<dae::GameObject>();
	sectionObserverGO->AddComponent(new LevelSectionObserver(sectionObserverGO, g_QBertGOs[0],
		pyramid, disksVector, 1, 2, true, true, 15.f, 10.f));
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

	// Disks
	diskGOsVector = MakeDiskGOsVector(2, 0);
	disksVector = new std::vector<Disk*>();
	for (size_t i = 0; i < diskGOsVector->size(); i++)
	{
		disksVector->push_back(diskGOsVector->operator[](i)->GetComponent<Disk>());
		scene3.Add(diskGOsVector->operator[](i));
	}

	// Transfer QBert
	for (const auto& gameObject : g_QBertGOs)
		scene3.Add(gameObject);

	// Make UI
	for (const auto& gameObject : uiGOs)
		scene3.Add(gameObject);

	// Level Section Observer
	sectionObserverGO = std::make_shared<dae::GameObject>();
	sectionObserverGO->AddComponent(new LevelSectionObserver(sectionObserverGO, g_QBertGOs[0],
		pyramid, disksVector, 1, 2, true, true, 10.f, 7.f));
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

	// Disks
	diskGOsVector = MakeDiskGOsVector(2, 4);
	disksVector = new std::vector<Disk*>();
	for (size_t i = 0; i < diskGOsVector->size(); i++)
	{
		disksVector->push_back(diskGOsVector->operator[](i)->GetComponent<Disk>());
		scene4.Add(diskGOsVector->operator[](i));
	}

	// Transfer QBert
	for (const auto& gameObject : g_QBertGOs)
		scene4.Add(gameObject);

	// Make UI
	for (const auto& gameObject : uiGOs)
		scene4.Add(gameObject);

	// Level Section Observer
	sectionObserverGO = std::make_shared<dae::GameObject>();
	sectionObserverGO->AddComponent(new LevelSectionObserver(sectionObserverGO, g_QBertGOs[0],
		pyramid, disksVector, 1, 2, true, true, 5.f, 5.f));
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
	for (const auto& gameObject : g_QBertGOs)
		scene1.Add(gameObject);

	// Disks
	auto* diskGOsVector = MakeDiskGOsVector(3, 5);
	auto* disksVector = new std::vector<Disk*>();
	for (size_t i = 0; i < diskGOsVector->size(); i++)
	{
		disksVector->push_back(diskGOsVector->operator[](i)->GetComponent<Disk>());
		scene1.Add(diskGOsVector->operator[](i));
	}

	// Make UI
	auto uiGOs = MakeUI(qBertsCompVector, false);
	for (const auto& gameObject : uiGOs)
		scene1.Add(gameObject);

	// Level Section Observer
	auto sectionObserverGO = std::make_shared<dae::GameObject>();
	sectionObserverGO->AddComponent(new LevelSectionObserver(sectionObserverGO, g_QBertGOs[0],
		pyramid, disksVector, 1, 3, true, true, 25.f, 15.f));
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
	for (const auto& gameObject : g_QBertGOs)
		scene2.Add(gameObject);

	// Disks
	diskGOsVector = MakeDiskGOsVector(3, 2);
	disksVector = new std::vector<Disk*>();
	for (size_t i = 0; i < diskGOsVector->size(); i++)
	{
		disksVector->push_back(diskGOsVector->operator[](i)->GetComponent<Disk>());
		scene2.Add(diskGOsVector->operator[](i));
	}

	// Make UI
	for (const auto& gameObject : uiGOs)
		scene2.Add(gameObject);

	// Level Section Observer
	sectionObserverGO = std::make_shared<dae::GameObject>();
	sectionObserverGO->AddComponent(new LevelSectionObserver(sectionObserverGO, g_QBertGOs[0],
		pyramid, disksVector, 1, 3, true, true, 20.f, 10.f));
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
	for (const auto& gameObject : g_QBertGOs)
		scene3.Add(gameObject);

	// Disks
	diskGOsVector = MakeDiskGOsVector(3, 1);
	disksVector = new std::vector<Disk*>();
	for (size_t i = 0; i < diskGOsVector->size(); i++)
	{
		disksVector->push_back(diskGOsVector->operator[](i)->GetComponent<Disk>());
		scene3.Add(diskGOsVector->operator[](i));
	}

	// Make UI
	for (const auto& gameObject : uiGOs)
		scene3.Add(gameObject);

	// Level Section Observer
	sectionObserverGO = std::make_shared<dae::GameObject>();
	sectionObserverGO->AddComponent(new LevelSectionObserver(sectionObserverGO, g_QBertGOs[0],
		pyramid, disksVector, 1, 3, true, true, 15.f, 7.f));
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
	for (const auto& gameObject : g_QBertGOs)
		scene4.Add(gameObject);

	// Disks
	diskGOsVector = MakeDiskGOsVector(3, 0);
	disksVector = new std::vector<Disk*>();
	for (size_t i = 0; i < diskGOsVector->size(); i++)
	{
		disksVector->push_back(diskGOsVector->operator[](i)->GetComponent<Disk>());
		scene4.Add(diskGOsVector->operator[](i));
	}

	// Make UI
	for (const auto& gameObject : uiGOs)
		scene4.Add(gameObject);

	// Level Section Observer
	sectionObserverGO = std::make_shared<dae::GameObject>();
	sectionObserverGO->AddComponent(new LevelSectionObserver(sectionObserverGO, g_QBertGOs[0],
		pyramid, disksVector, 1, 3, true, true, 10.f, 5.f));
	scene4.Add(sectionObserverGO);

	// FPS Counter
	scene4.Add(MakeFPSCounter());
}

void LoadVictoryScreen()
{
	// Create Scene
	auto& victoryScene = dae::SceneManager::GetInstance().CreateScene("VictoryScene");

	// Add All Needed Game Objects
	victoryScene.Add(MakeVictoryScreenVisuals());
	const auto victoryScreenGO = MakeVictoryDeathScreenLogic(0, g_QBertGOs[0]->GetComponent<QBert>());
	victoryScene.Add(victoryScreenGO);

	// Add The Victory/Death Screen Player Input
	auto menuPlayerInputGO = std::make_shared<dae::GameObject>();
	menuPlayerInputGO->AddComponent(new VictoryDeathScreenInput(victoryScreenGO));
	victoryScene.Add(menuPlayerInputGO);
}

void SetUpGlobalGOs()
{
	// QBert
	g_QBertGOs = MakeQBert();
	qBertsCompVector->push_back(g_QBertGOs[0]->GetComponent<QBert>());
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