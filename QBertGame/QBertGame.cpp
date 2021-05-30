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

// To create and read binary files
#include<fstream>


// Global Variables
const int g_CubesSpriteHeight = 32;
const int g_CubesSpriteWidth = 32;
const float g_PyramidPosX = 300.f;
const float g_PyramidPosY = 80.f;
std::vector<std::shared_ptr<dae::GameObject>> g_QBertGOs;
auto* qBertsCompVector = new std::vector<QBert*>();


// Global Functions
void SetUpGlobalGOs();
void PrintInstructions();

void LoadDeathScreen();
void LoadStartScreen();
void LoadVictoryScreen();

void CreateBinaryLevel01();
void CreateBinaryLevel02();
void CreateBinaryLevel03();
void LoadLevelsBinaries(const std::string& fileName);

// Only for testing, not using bin files
void LoadLevel01();
void LoadLevel02();
void LoadLevel03();


// Struct used to read and write the binary files of each level
struct Round
{
	int roundNumber;
	int level;
	int colorIdx;
	bool spawnSlickSams;
	bool spawnUggWrongs;
	float slickSamsSpawnInterval;
	float uggWrongSpawnInterval;
	bool isCoop;
};




int main(int, char* [])
{
	srand((unsigned)time(nullptr));

	CreateBinaryLevel01();
	CreateBinaryLevel02();
	CreateBinaryLevel03();
	
    dae::Minigin engine;
    engine.Initialize();

	//engine.LoadDemo();
	
	SetUpGlobalGOs();
	LoadStartScreen();
	LoadDeathScreen();
	LoadLevelsBinaries("Level01.bin");
	LoadLevelsBinaries("Level02.bin");
	LoadLevelsBinaries("Level03.bin");
	LoadVictoryScreen();
	PrintInstructions();
	
	engine.Run();
	
    return 0;
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




void CreateBinaryLevel01()
{	
	std::ofstream levelOne("Level01.bin", std::ios::out | std::ios::binary);
	
	if (!levelOne)
		std::cout << "Level 01 file couldn't be created\n";

	const int nrRounds = 4;
	Round rounds[nrRounds];
	
	rounds[0].roundNumber = 1;
	rounds[0].level = 1;
	rounds[0].colorIdx = 0;
	rounds[0].spawnSlickSams = false;
	rounds[0].spawnUggWrongs = false;
	rounds[0].slickSamsSpawnInterval = 0.f;
	rounds[0].uggWrongSpawnInterval = 0.f;
	rounds[0].isCoop = false;

	rounds[1].roundNumber = 2;
	rounds[1].level = 1;
	rounds[1].colorIdx = 1;
	rounds[1].spawnSlickSams = false;
	rounds[1].spawnUggWrongs = false;
	rounds[1].slickSamsSpawnInterval = 0.f;
	rounds[1].uggWrongSpawnInterval = 0.f;
	rounds[1].isCoop = false;

	rounds[2].roundNumber = 3;
	rounds[2].level = 1;
	rounds[2].colorIdx = 2;
	rounds[2].spawnSlickSams = false;
	rounds[2].spawnUggWrongs = true;
	rounds[2].slickSamsSpawnInterval = 0.f;
	rounds[2].uggWrongSpawnInterval = 10.f;
	rounds[2].isCoop = false;

	rounds[3].roundNumber = 4;
	rounds[3].level = 1;
	rounds[3].colorIdx = 3;
	rounds[3].spawnSlickSams = false;
	rounds[3].spawnUggWrongs = true;
	rounds[3].slickSamsSpawnInterval = 0.f;
	rounds[3].uggWrongSpawnInterval = 7.f;
	rounds[3].isCoop = false;
	
	for (int i = 0; i < nrRounds; i++)
		levelOne.write((char*)&rounds[i], sizeof(Round));
	
	levelOne.close();
	
	if (!levelOne.good())
		std::cout << "Level 01 file wasn't properly written\n";
}

void CreateBinaryLevel02()
{
	std::ofstream levelTwo("Level02.bin", std::ios::out | std::ios::binary);

	if (!levelTwo)
		std::cout << "Level 02 file couldn't be created\n";

	const int nrRounds = 4;
	Round rounds[nrRounds];

	rounds[0].roundNumber = 1;
	rounds[0].level = 2;
	rounds[0].colorIdx = 1;
	rounds[0].spawnSlickSams = true;
	rounds[0].spawnUggWrongs = true;
	rounds[0].slickSamsSpawnInterval = 15.f;
	rounds[0].uggWrongSpawnInterval = 15.f;
	rounds[0].isCoop = false;

	rounds[1].roundNumber = 2;
	rounds[1].level = 2;
	rounds[1].colorIdx = 3;
	rounds[1].spawnSlickSams = true;
	rounds[1].spawnUggWrongs = true;
	rounds[1].slickSamsSpawnInterval = 13.f;
	rounds[1].uggWrongSpawnInterval = 10.f;
	rounds[1].isCoop = false;

	rounds[2].roundNumber = 3;
	rounds[2].level = 2;
	rounds[2].colorIdx = 0;
	rounds[2].spawnSlickSams = true;
	rounds[2].spawnUggWrongs = true;
	rounds[2].slickSamsSpawnInterval = 10.f;
	rounds[2].uggWrongSpawnInterval = 7.f;
	rounds[2].isCoop = false;

	rounds[3].roundNumber = 4;
	rounds[3].level = 2;
	rounds[3].colorIdx = 4;
	rounds[3].spawnSlickSams = true;
	rounds[3].spawnUggWrongs = true;
	rounds[3].slickSamsSpawnInterval = 10.f;
	rounds[3].uggWrongSpawnInterval = 5.f;
	rounds[3].isCoop = false;

	for (int i = 0; i < nrRounds; i++)
		levelTwo.write((char*)&rounds[i], sizeof(Round));

	levelTwo.close();

	if (!levelTwo.good())
		std::cout << "Level 02 file wasn't properly written\n";
}

void CreateBinaryLevel03()
{
	std::ofstream levelThree("Level03.bin", std::ios::out | std::ios::binary);

	if (!levelThree)
		std::cout << "Level 03 file couldn't be created\n";

	const int nrRounds = 4;
	Round rounds[nrRounds];

	rounds[0].roundNumber = 1;
	rounds[0].level = 3;
	rounds[0].colorIdx = 5;
	rounds[0].spawnSlickSams = true;
	rounds[0].spawnUggWrongs = true;
	rounds[0].slickSamsSpawnInterval = 25.f;
	rounds[0].uggWrongSpawnInterval = 15.f;
	rounds[0].isCoop = false;

	rounds[1].roundNumber = 2;
	rounds[1].level = 3;
	rounds[1].colorIdx = 2;
	rounds[1].spawnSlickSams = true;
	rounds[1].spawnUggWrongs = true;
	rounds[1].slickSamsSpawnInterval = 20.f;
	rounds[1].uggWrongSpawnInterval = 10.f;
	rounds[1].isCoop = false;

	rounds[2].roundNumber = 3;
	rounds[2].level = 3;
	rounds[2].colorIdx = 1;
	rounds[2].spawnSlickSams = true;
	rounds[2].spawnUggWrongs = true;
	rounds[2].slickSamsSpawnInterval = 15.f;
	rounds[2].uggWrongSpawnInterval = 7.f;
	rounds[2].isCoop = false;

	rounds[3].roundNumber = 4;
	rounds[3].level = 3;
	rounds[3].colorIdx = 0;
	rounds[3].spawnSlickSams = true;
	rounds[3].spawnUggWrongs = true;
	rounds[3].slickSamsSpawnInterval = 10.f;
	rounds[3].uggWrongSpawnInterval = 5.f;
	rounds[3].isCoop = false;

	for (int i = 0; i < nrRounds; i++)
		levelThree.write((char*)&rounds[i], sizeof(Round));

	levelThree.close();

	if (!levelThree.good())
		std::cout << "Level 03 file wasn't properly written\n";
}

void LoadLevelsBinaries(const std::string& fileName)
{
	const int nrRounds = 4;
	
	//// Extract information from binary file into local array
	
	std::ifstream levelFile(fileName, std::ios::out | std::ios::binary);
	
	if (!levelFile)
		std::cout << "Level file '" << fileName << "' couldn't be opened\n";;
	
	Round rounds[4];
	
	for (int i = 0; i < nrRounds; i++)
		levelFile.read((char*)&rounds[i], sizeof(Round));
	
	levelFile.close();
	
	if (!levelFile.good())
		std::cout << "Level file '" << fileName << "' wasn't read properly\n" << std::endl;


	
	//// Level Title Screen

	// Create Scene
	std::string levelTitleSceneName = "Level0";
	levelTitleSceneName += std::to_string(rounds[0].level);
	levelTitleSceneName += "Title";
	auto& levelTitleScene = dae::SceneManager::GetInstance().CreateScene(levelTitleSceneName);

	// Add All Needed Game Objects
	levelTitleScene.Add(MakeLevelTitle(rounds[0].level));
	levelTitleScene.Add(MakeLevelTransition(g_QBertGOs[0]->GetComponent<QBert>()));


	
	//// Create A Scene And Fill It Properly For Each Round
	
	for(const auto& round : rounds)
	{
		// Create Scene
		std::string sceneName = "Level0";
		levelTitleSceneName += std::to_string(rounds[0].level);
		levelTitleSceneName += "-";
		levelTitleSceneName += std::to_string(rounds[0].roundNumber);
		auto& scene = dae::SceneManager::GetInstance().CreateScene(sceneName);

		// Level Map
		auto* pyramid = new Pyramid(g_PyramidPosX, g_PyramidPosY, g_NrRows, g_CubesActualWidth, g_CubesActualHeight,
			round.colorIdx, round.level, g_CubesSpriteWidth, g_CubesSpriteHeight);
		for (const std::shared_ptr<dae::GameObject>& cube : pyramid->m_CubeGOVector)
			scene.Add(cube);

		// Disks
		auto* diskGOsVector = MakeDiskGOsVector(round.level, round.colorIdx);
		auto* disksVector = new std::vector<Disk*>();
		for (size_t i = 0; i < diskGOsVector->size(); i++)
		{
			disksVector->push_back(diskGOsVector->operator[](i)->GetComponent<Disk>());
			scene.Add(diskGOsVector->operator[](i));
		}

		// Transfer QBert
		for (const auto& gameObject : g_QBertGOs)
			scene.Add(gameObject);

		// Make UI
		auto uiGOs = MakeUI(qBertsCompVector, round.isCoop);
		for (const auto& gameObject : uiGOs)
			scene.Add(gameObject);

		// Level Section Observer
		auto sectionObserverGO = std::make_shared<dae::GameObject>();
		sectionObserverGO->AddComponent(new LevelSectionObserver(sectionObserverGO, g_QBertGOs[0], pyramid, disksVector, 1, round.level,
			round.spawnSlickSams, round.spawnUggWrongs, round.slickSamsSpawnInterval, round.uggWrongSpawnInterval));
		scene.Add(sectionObserverGO);

		// Add The Mode's Player Input
		auto gamePlayerInputGO = std::make_shared<dae::GameObject>();
		gamePlayerInputGO->AddComponent(new PlayerOneInput(g_QBertGOs[0]));
		scene.Add(gamePlayerInputGO);
	}
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
	auto& scene1 = dae::SceneManager::GetInstance().CreateScene("Level01-1");

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
	auto& scene2 = dae::SceneManager::GetInstance().CreateScene("Level01-2");

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
	auto& scene3 = dae::SceneManager::GetInstance().CreateScene("Level01-3");

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
	auto& scene4 = dae::SceneManager::GetInstance().CreateScene("Level01-4");

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
	auto& levelTitleScene = dae::SceneManager::GetInstance().CreateScene("Level02Title");

	// Add All Needed Game Objects
	levelTitleScene.Add(MakeLevelTitle(2));
	levelTitleScene.Add(MakeLevelTransition(g_QBertGOs[0]->GetComponent<QBert>()));



	//// Section 01

	// Create Scene
	auto& scene1 = dae::SceneManager::GetInstance().CreateScene("Level02-1");

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
		pyramid, disksVector, 1, 2, true, true, 15.f, 15.f));
	scene1.Add(sectionObserverGO);

	// FPS Counter
	scene1.Add(MakeFPSCounter());


	//////////////////////////


	//// Section 02

	// Create Scene
	auto& scene2 = dae::SceneManager::GetInstance().CreateScene("Level02-2");

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
		pyramid, disksVector, 1, 2, true, true, 13.f, 10.f));
	scene2.Add(sectionObserverGO);

	// FPS Counter
	scene2.Add(MakeFPSCounter());


	//////////////////////////


	//// Section 03

	// Create Scene
	auto& scene3 = dae::SceneManager::GetInstance().CreateScene("Level02-3");

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
	auto& scene4 = dae::SceneManager::GetInstance().CreateScene("Level02-4");

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
		pyramid, disksVector, 1, 2, true, true, 10.f, 5.f));
	scene4.Add(sectionObserverGO);

	// FPS Counter
	scene4.Add(MakeFPSCounter());
}

void LoadLevel03()
{
	//// Level Title Screen

	// Create Scene
	auto& levelTitleScene = dae::SceneManager::GetInstance().CreateScene("Level03Title");

	// Add All Needed Game Objects
	levelTitleScene.Add(MakeLevelTitle(3));
	levelTitleScene.Add(MakeLevelTransition(g_QBertGOs[0]->GetComponent<QBert>()));



	//// Section 01

	// Create Scene
	auto& scene1 = dae::SceneManager::GetInstance().CreateScene("Level03-1");

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
	auto& scene2 = dae::SceneManager::GetInstance().CreateScene("Level03-2");

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
	auto& scene3 = dae::SceneManager::GetInstance().CreateScene("Level03-3");

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
	auto& scene4 = dae::SceneManager::GetInstance().CreateScene("Level03-4");

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