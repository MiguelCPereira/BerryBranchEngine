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

void LoadStartScreen();
void LoadDeathScreenSolo();
void LoadVictoryScreenSolo();
void LoadDeathScreenVersus();
void LoadVictoryScreenVersus();

void CreateBinaryLevel01Solo();
void CreateBinaryLevel02Solo();
void CreateBinaryLevel03Solo();
void CreateBinaryLevel01Coop();
void CreateBinaryLevel02Coop();
void CreateBinaryLevel03Coop();
void CreateBinaryLevel01Versus();
void CreateBinaryLevel02Versus();
void CreateBinaryLevel03Versus();

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
	int gameMode; // 1 is solo, 2 is coop, 3 is versus
};




int main(int, char* [])
{
	srand((unsigned)time(nullptr));

	CreateBinaryLevel01Solo();
	CreateBinaryLevel02Solo();
	CreateBinaryLevel03Solo();
	CreateBinaryLevel01Coop();
	CreateBinaryLevel02Coop();
	CreateBinaryLevel03Coop();
	CreateBinaryLevel01Versus();
	CreateBinaryLevel02Versus();
	CreateBinaryLevel03Versus();
	
    dae::Minigin engine;
    engine.Initialize();

	//engine.LoadDemo();
	
	SetUpGlobalGOs();
	LoadStartScreen(); // Scene idx 00
	LoadDeathScreenSolo(); // Scene idx 01
	LoadLevelsBinaries("Level01Solo.bin"); // Scene idx 02-06
	LoadLevelsBinaries("Level02Solo.bin"); // Scene idx 07-11
	LoadLevelsBinaries("Level03Solo.bin"); // Scene idx 12-16
	LoadVictoryScreenSolo(); // Scene idx 17
	LoadDeathScreenVersus(); // Scene idx 18
	LoadLevelsBinaries("Level01Versus.bin"); // Scene idx 19-23
	LoadLevelsBinaries("Level02Versus.bin"); // Scene idx 24-28
	LoadLevelsBinaries("Level03Versus.bin"); // Scene idx 29-33
	LoadVictoryScreenVersus(); // Scene idx 34
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





void CreateBinaryLevel01Solo()
{	
	std::ofstream levelOne("Level01Solo.bin", std::ios::out | std::ios::binary);
	
	if (!levelOne)
		std::cout << "Level 01 Solo file couldn't be created\n";

	const int nrRounds = 4;
	Round rounds[nrRounds];
	
	rounds[0].roundNumber = 1;
	rounds[0].level = 1;
	rounds[0].colorIdx = 0;
	rounds[0].spawnSlickSams = false;
	rounds[0].spawnUggWrongs = false;
	rounds[0].slickSamsSpawnInterval = 0.f;
	rounds[0].uggWrongSpawnInterval = 0.f;
	rounds[0].gameMode = 1;

	rounds[1].roundNumber = 2;
	rounds[1].level = 1;
	rounds[1].colorIdx = 1;
	rounds[1].spawnSlickSams = false;
	rounds[1].spawnUggWrongs = false;
	rounds[1].slickSamsSpawnInterval = 0.f;
	rounds[1].uggWrongSpawnInterval = 0.f;
	rounds[1].gameMode = 1;

	rounds[2].roundNumber = 3;
	rounds[2].level = 1;
	rounds[2].colorIdx = 2;
	rounds[2].spawnSlickSams = false;
	rounds[2].spawnUggWrongs = true;
	rounds[2].slickSamsSpawnInterval = 0.f;
	rounds[2].uggWrongSpawnInterval = 10.f;
	rounds[2].gameMode = 1;

	rounds[3].roundNumber = 4;
	rounds[3].level = 1;
	rounds[3].colorIdx = 3;
	rounds[3].spawnSlickSams = false;
	rounds[3].spawnUggWrongs = true;
	rounds[3].slickSamsSpawnInterval = 0.f;
	rounds[3].uggWrongSpawnInterval = 7.f;
	rounds[3].gameMode = 1;
	
	for (int i = 0; i < nrRounds; i++)
		levelOne.write((char*)&rounds[i], sizeof(Round));
	
	levelOne.close();
	
	if (!levelOne.good())
		std::cout << "Level 01 Solo file wasn't properly written\n";
}

void CreateBinaryLevel02Solo()
{
	std::ofstream levelTwo("Level02Solo.bin", std::ios::out | std::ios::binary);

	if (!levelTwo)
		std::cout << "Level 02 Solo file couldn't be created\n";

	const int nrRounds = 4;
	Round rounds[nrRounds];

	rounds[0].roundNumber = 1;
	rounds[0].level = 2;
	rounds[0].colorIdx = 1;
	rounds[0].spawnSlickSams = true;
	rounds[0].spawnUggWrongs = true;
	rounds[0].slickSamsSpawnInterval = 15.f;
	rounds[0].uggWrongSpawnInterval = 15.f;
	rounds[0].gameMode = 1;

	rounds[1].roundNumber = 2;
	rounds[1].level = 2;
	rounds[1].colorIdx = 3;
	rounds[1].spawnSlickSams = true;
	rounds[1].spawnUggWrongs = true;
	rounds[1].slickSamsSpawnInterval = 13.f;
	rounds[1].uggWrongSpawnInterval = 10.f;
	rounds[1].gameMode = 1;

	rounds[2].roundNumber = 3;
	rounds[2].level = 2;
	rounds[2].colorIdx = 0;
	rounds[2].spawnSlickSams = true;
	rounds[2].spawnUggWrongs = true;
	rounds[2].slickSamsSpawnInterval = 10.f;
	rounds[2].uggWrongSpawnInterval = 7.f;
	rounds[2].gameMode = 1;

	rounds[3].roundNumber = 4;
	rounds[3].level = 2;
	rounds[3].colorIdx = 4;
	rounds[3].spawnSlickSams = true;
	rounds[3].spawnUggWrongs = true;
	rounds[3].slickSamsSpawnInterval = 10.f;
	rounds[3].uggWrongSpawnInterval = 5.f;
	rounds[3].gameMode = 1;

	for (int i = 0; i < nrRounds; i++)
		levelTwo.write((char*)&rounds[i], sizeof(Round));

	levelTwo.close();

	if (!levelTwo.good())
		std::cout << "Level 02 Solo file wasn't properly written\n";
}

void CreateBinaryLevel03Solo()
{
	std::ofstream levelThree("Level03Solo.bin", std::ios::out | std::ios::binary);

	if (!levelThree)
		std::cout << "Level 03 Solo file couldn't be created\n";

	const int nrRounds = 4;
	Round rounds[nrRounds];

	rounds[0].roundNumber = 1;
	rounds[0].level = 3;
	rounds[0].colorIdx = 5;
	rounds[0].spawnSlickSams = true;
	rounds[0].spawnUggWrongs = true;
	rounds[0].slickSamsSpawnInterval = 25.f;
	rounds[0].uggWrongSpawnInterval = 15.f;
	rounds[0].gameMode = 1;

	rounds[1].roundNumber = 2;
	rounds[1].level = 3;
	rounds[1].colorIdx = 2;
	rounds[1].spawnSlickSams = true;
	rounds[1].spawnUggWrongs = true;
	rounds[1].slickSamsSpawnInterval = 20.f;
	rounds[1].uggWrongSpawnInterval = 10.f;
	rounds[1].gameMode = 1;

	rounds[2].roundNumber = 3;
	rounds[2].level = 3;
	rounds[2].colorIdx = 1;
	rounds[2].spawnSlickSams = true;
	rounds[2].spawnUggWrongs = true;
	rounds[2].slickSamsSpawnInterval = 15.f;
	rounds[2].uggWrongSpawnInterval = 7.f;
	rounds[2].gameMode = 1;

	rounds[3].roundNumber = 4;
	rounds[3].level = 3;
	rounds[3].colorIdx = 0;
	rounds[3].spawnSlickSams = true;
	rounds[3].spawnUggWrongs = true;
	rounds[3].slickSamsSpawnInterval = 10.f;
	rounds[3].uggWrongSpawnInterval = 5.f;
	rounds[3].gameMode = 1;

	for (int i = 0; i < nrRounds; i++)
		levelThree.write((char*)&rounds[i], sizeof(Round));

	levelThree.close();

	if (!levelThree.good())
		std::cout << "Level 03 Solo file wasn't properly written\n";
}


void CreateBinaryLevel01Coop()
{
	std::ofstream levelOne("Level01Coop.bin", std::ios::out | std::ios::binary);

	if (!levelOne)
		std::cout << "Level 01 Co-op file couldn't be created\n";

	const int nrRounds = 4;
	Round rounds[nrRounds];

	rounds[0].roundNumber = 1;
	rounds[0].level = 1;
	rounds[0].colorIdx = 0;
	rounds[0].spawnSlickSams = false;
	rounds[0].spawnUggWrongs = false;
	rounds[0].slickSamsSpawnInterval = 0.f;
	rounds[0].uggWrongSpawnInterval = 0.f;
	rounds[0].gameMode = 2;

	rounds[1].roundNumber = 2;
	rounds[1].level = 1;
	rounds[1].colorIdx = 1;
	rounds[1].spawnSlickSams = false;
	rounds[1].spawnUggWrongs = false;
	rounds[1].slickSamsSpawnInterval = 0.f;
	rounds[1].uggWrongSpawnInterval = 0.f;
	rounds[1].gameMode = 2;

	rounds[2].roundNumber = 3;
	rounds[2].level = 1;
	rounds[2].colorIdx = 2;
	rounds[2].spawnSlickSams = false;
	rounds[2].spawnUggWrongs = true;
	rounds[2].slickSamsSpawnInterval = 0.f;
	rounds[2].uggWrongSpawnInterval = 10.f;
	rounds[2].gameMode = 2;

	rounds[3].roundNumber = 4;
	rounds[3].level = 1;
	rounds[3].colorIdx = 3;
	rounds[3].spawnSlickSams = false;
	rounds[3].spawnUggWrongs = true;
	rounds[3].slickSamsSpawnInterval = 0.f;
	rounds[3].uggWrongSpawnInterval = 7.f;
	rounds[3].gameMode = 2;

	for (int i = 0; i < nrRounds; i++)
		levelOne.write((char*)&rounds[i], sizeof(Round));

	levelOne.close();

	if (!levelOne.good())
		std::cout << "Level 01 Co-op file wasn't properly written\n";
}

void CreateBinaryLevel02Coop()
{
	std::ofstream levelTwo("Level02Coop.bin", std::ios::out | std::ios::binary);

	if (!levelTwo)
		std::cout << "Level 02 Co-op file couldn't be created\n";

	const int nrRounds = 4;
	Round rounds[nrRounds];

	rounds[0].roundNumber = 1;
	rounds[0].level = 2;
	rounds[0].colorIdx = 1;
	rounds[0].spawnSlickSams = true;
	rounds[0].spawnUggWrongs = true;
	rounds[0].slickSamsSpawnInterval = 15.f;
	rounds[0].uggWrongSpawnInterval = 15.f;
	rounds[0].gameMode = 2;

	rounds[1].roundNumber = 2;
	rounds[1].level = 2;
	rounds[1].colorIdx = 3;
	rounds[1].spawnSlickSams = true;
	rounds[1].spawnUggWrongs = true;
	rounds[1].slickSamsSpawnInterval = 13.f;
	rounds[1].uggWrongSpawnInterval = 10.f;
	rounds[1].gameMode = 2;

	rounds[2].roundNumber = 3;
	rounds[2].level = 2;
	rounds[2].colorIdx = 0;
	rounds[2].spawnSlickSams = true;
	rounds[2].spawnUggWrongs = true;
	rounds[2].slickSamsSpawnInterval = 10.f;
	rounds[2].uggWrongSpawnInterval = 7.f;
	rounds[2].gameMode = 2;

	rounds[3].roundNumber = 4;
	rounds[3].level = 2;
	rounds[3].colorIdx = 4;
	rounds[3].spawnSlickSams = true;
	rounds[3].spawnUggWrongs = true;
	rounds[3].slickSamsSpawnInterval = 10.f;
	rounds[3].uggWrongSpawnInterval = 5.f;
	rounds[3].gameMode = 2;

	for (int i = 0; i < nrRounds; i++)
		levelTwo.write((char*)&rounds[i], sizeof(Round));

	levelTwo.close();

	if (!levelTwo.good())
		std::cout << "Level 02 Co-op file wasn't properly written\n";
}

void CreateBinaryLevel03Coop()
{
	std::ofstream levelThree("Level03Coop.bin", std::ios::out | std::ios::binary);

	if (!levelThree)
		std::cout << "Level 03 Co-op file couldn't be created\n";

	const int nrRounds = 4;
	Round rounds[nrRounds];

	rounds[0].roundNumber = 1;
	rounds[0].level = 3;
	rounds[0].colorIdx = 5;
	rounds[0].spawnSlickSams = true;
	rounds[0].spawnUggWrongs = true;
	rounds[0].slickSamsSpawnInterval = 25.f;
	rounds[0].uggWrongSpawnInterval = 15.f;
	rounds[0].gameMode = 2;

	rounds[1].roundNumber = 2;
	rounds[1].level = 3;
	rounds[1].colorIdx = 2;
	rounds[1].spawnSlickSams = true;
	rounds[1].spawnUggWrongs = true;
	rounds[1].slickSamsSpawnInterval = 20.f;
	rounds[1].uggWrongSpawnInterval = 10.f;
	rounds[1].gameMode = 2;

	rounds[2].roundNumber = 3;
	rounds[2].level = 3;
	rounds[2].colorIdx = 1;
	rounds[2].spawnSlickSams = true;
	rounds[2].spawnUggWrongs = true;
	rounds[2].slickSamsSpawnInterval = 15.f;
	rounds[2].uggWrongSpawnInterval = 7.f;
	rounds[2].gameMode = 2;

	rounds[3].roundNumber = 4;
	rounds[3].level = 3;
	rounds[3].colorIdx = 0;
	rounds[3].spawnSlickSams = true;
	rounds[3].spawnUggWrongs = true;
	rounds[3].slickSamsSpawnInterval = 10.f;
	rounds[3].uggWrongSpawnInterval = 5.f;
	rounds[3].gameMode = 2;

	for (int i = 0; i < nrRounds; i++)
		levelThree.write((char*)&rounds[i], sizeof(Round));

	levelThree.close();

	if (!levelThree.good())
		std::cout << "Level 03 Co-op file wasn't properly written\n";
}


void CreateBinaryLevel01Versus()
{
	std::ofstream levelOne("Level01Versus.bin", std::ios::out | std::ios::binary);

	if (!levelOne)
		std::cout << "Level 01 Versus file couldn't be created\n";

	const int nrRounds = 4;
	Round rounds[nrRounds];

	rounds[0].roundNumber = 1;
	rounds[0].level = 1;
	rounds[0].colorIdx = 0;
	rounds[0].spawnSlickSams = false;
	rounds[0].spawnUggWrongs = false;
	rounds[0].slickSamsSpawnInterval = 0.f;
	rounds[0].uggWrongSpawnInterval = 0.f;
	rounds[0].gameMode = 3;

	rounds[1].roundNumber = 2;
	rounds[1].level = 1;
	rounds[1].colorIdx = 1;
	rounds[1].spawnSlickSams = false;
	rounds[1].spawnUggWrongs = false;
	rounds[1].slickSamsSpawnInterval = 0.f;
	rounds[1].uggWrongSpawnInterval = 0.f;
	rounds[1].gameMode = 3;

	rounds[2].roundNumber = 3;
	rounds[2].level = 1;
	rounds[2].colorIdx = 2;
	rounds[2].spawnSlickSams = false;
	rounds[2].spawnUggWrongs = true;
	rounds[2].slickSamsSpawnInterval = 0.f;
	rounds[2].uggWrongSpawnInterval = 10.f;
	rounds[2].gameMode = 3;

	rounds[3].roundNumber = 4;
	rounds[3].level = 1;
	rounds[3].colorIdx = 3;
	rounds[3].spawnSlickSams = false;
	rounds[3].spawnUggWrongs = true;
	rounds[3].slickSamsSpawnInterval = 0.f;
	rounds[3].uggWrongSpawnInterval = 7.f;
	rounds[3].gameMode = 3;

	for (int i = 0; i < nrRounds; i++)
		levelOne.write((char*)&rounds[i], sizeof(Round));

	levelOne.close();

	if (!levelOne.good())
		std::cout << "Level 01 Versus file wasn't properly written\n";
}

void CreateBinaryLevel02Versus()
{
	std::ofstream levelTwo("Level02Versus.bin", std::ios::out | std::ios::binary);

	if (!levelTwo)
		std::cout << "Level 02 Versus file couldn't be created\n";

	const int nrRounds = 4;
	Round rounds[nrRounds];

	rounds[0].roundNumber = 1;
	rounds[0].level = 2;
	rounds[0].colorIdx = 1;
	rounds[0].spawnSlickSams = true;
	rounds[0].spawnUggWrongs = true;
	rounds[0].slickSamsSpawnInterval = 15.f;
	rounds[0].uggWrongSpawnInterval = 15.f;
	rounds[0].gameMode = 3;

	rounds[1].roundNumber = 2;
	rounds[1].level = 2;
	rounds[1].colorIdx = 3;
	rounds[1].spawnSlickSams = true;
	rounds[1].spawnUggWrongs = true;
	rounds[1].slickSamsSpawnInterval = 13.f;
	rounds[1].uggWrongSpawnInterval = 10.f;
	rounds[1].gameMode = 3;

	rounds[2].roundNumber = 3;
	rounds[2].level = 2;
	rounds[2].colorIdx = 0;
	rounds[2].spawnSlickSams = true;
	rounds[2].spawnUggWrongs = true;
	rounds[2].slickSamsSpawnInterval = 10.f;
	rounds[2].uggWrongSpawnInterval = 7.f;
	rounds[2].gameMode = 3;

	rounds[3].roundNumber = 4;
	rounds[3].level = 2;
	rounds[3].colorIdx = 4;
	rounds[3].spawnSlickSams = true;
	rounds[3].spawnUggWrongs = true;
	rounds[3].slickSamsSpawnInterval = 10.f;
	rounds[3].uggWrongSpawnInterval = 5.f;
	rounds[3].gameMode = 3;

	for (int i = 0; i < nrRounds; i++)
		levelTwo.write((char*)&rounds[i], sizeof(Round));

	levelTwo.close();

	if (!levelTwo.good())
		std::cout << "Level 02 Versus file wasn't properly written\n";
}

void CreateBinaryLevel03Versus()
{
	std::ofstream levelThree("Level03Versus.bin", std::ios::out | std::ios::binary);

	if (!levelThree)
		std::cout << "Level 03 Versus file couldn't be created\n";

	const int nrRounds = 4;
	Round rounds[nrRounds];

	rounds[0].roundNumber = 1;
	rounds[0].level = 3;
	rounds[0].colorIdx = 5;
	rounds[0].spawnSlickSams = true;
	rounds[0].spawnUggWrongs = true;
	rounds[0].slickSamsSpawnInterval = 25.f;
	rounds[0].uggWrongSpawnInterval = 15.f;
	rounds[0].gameMode = 3;

	rounds[1].roundNumber = 2;
	rounds[1].level = 3;
	rounds[1].colorIdx = 2;
	rounds[1].spawnSlickSams = true;
	rounds[1].spawnUggWrongs = true;
	rounds[1].slickSamsSpawnInterval = 20.f;
	rounds[1].uggWrongSpawnInterval = 10.f;
	rounds[1].gameMode = 3;

	rounds[2].roundNumber = 3;
	rounds[2].level = 3;
	rounds[2].colorIdx = 1;
	rounds[2].spawnSlickSams = true;
	rounds[2].spawnUggWrongs = true;
	rounds[2].slickSamsSpawnInterval = 15.f;
	rounds[2].uggWrongSpawnInterval = 7.f;
	rounds[2].gameMode = 3;

	rounds[3].roundNumber = 4;
	rounds[3].level = 3;
	rounds[3].colorIdx = 0;
	rounds[3].spawnSlickSams = true;
	rounds[3].spawnUggWrongs = true;
	rounds[3].slickSamsSpawnInterval = 10.f;
	rounds[3].uggWrongSpawnInterval = 5.f;
	rounds[3].gameMode = 3;

	for (int i = 0; i < nrRounds; i++)
		levelThree.write((char*)&rounds[i], sizeof(Round));

	levelThree.close();

	if (!levelThree.good())
		std::cout << "Level 03 Versus file wasn't properly written\n";
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
	
	if (rounds[0].gameMode == 1)
		levelTitleSceneName += "Solo";
	else if(rounds[0].gameMode == 2)
		levelTitleSceneName += "Coop";
	else
		levelTitleSceneName += "Versus";
	
	auto& levelTitleScene = dae::SceneManager::GetInstance().CreateScene(levelTitleSceneName);

	// Add All Needed Game Objects
	levelTitleScene.Add(MakeLevelTitle(rounds[0].level, rounds[0].gameMode));
	levelTitleScene.Add(MakeLevelTransition(g_QBertGOs[0]->GetComponent<QBert>()));


	
	//// Create A Scene And Fill It Properly For Each Round
	
	for(const auto& round : rounds)
	{
		// Create Scene
		std::string sceneName = "Level0";
		sceneName += std::to_string(round.level);
		sceneName += "-";
		sceneName += std::to_string(round.roundNumber);

		if (rounds[0].gameMode == 1)
			sceneName += "Solo";
		else if (rounds[0].gameMode == 2)
			sceneName += "Coop";
		else
			sceneName += "Versus";
		
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
		std::vector<std::shared_ptr<dae::GameObject>> uiGOs;
		
		if(round.gameMode == 2)
			uiGOs = MakeUI(qBertsCompVector, true);
		else
			uiGOs = MakeUI(qBertsCompVector, false);
		
		for (const auto& gameObject : uiGOs)
			scene.Add(gameObject);

		// Level Section Observer
		int deathSceneIdx;
		if (round.gameMode == 1) // Solo
			deathSceneIdx = 1;
		else if (round.gameMode == 3) // Versus
			deathSceneIdx = 18;
		else					// Co-op
			deathSceneIdx = 1;
		
		auto sectionObserverGO = std::make_shared<dae::GameObject>();
		if (round.gameMode == 3)
		{
			sectionObserverGO->AddComponent(new LevelSectionObserver(sectionObserverGO, g_QBertGOs[0], pyramid, disksVector, deathSceneIdx, round.level,
				true, round.spawnSlickSams, round.spawnUggWrongs, round.slickSamsSpawnInterval, round.uggWrongSpawnInterval));
		}
		else
		{
			sectionObserverGO->AddComponent(new LevelSectionObserver(sectionObserverGO, g_QBertGOs[0], pyramid, disksVector, deathSceneIdx, round.level,
				false, round.spawnSlickSams, round.spawnUggWrongs, round.slickSamsSpawnInterval, round.uggWrongSpawnInterval));
		}
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
	const auto startScreenGO = MakeStartScreenLogic(2, 2, 19);
	startScreenScene.Add(startScreenGO);

	// Add The Start Menu Player Input
	auto menuPlayerInputGO = std::make_shared<dae::GameObject>();
	menuPlayerInputGO->AddComponent(new StartScreenInput(startScreenGO));
	startScreenScene.Add(menuPlayerInputGO);

	// Initialize Scene
	startScreenScene.Initialize();
}

void LoadDeathScreenSolo()
{
	// Create Scene
	auto& deathScreenScene = dae::SceneManager::GetInstance().CreateScene("DeathScreenSolo");

	// Add All Needed Game Objects
	deathScreenScene.Add(MakeDeathScreenSoloVisuals());
	const auto deathScreenGO = MakeVictoryDeathScreenLogic(0, g_QBertGOs[0]->GetComponent<QBert>());
	deathScreenScene.Add(deathScreenGO);

	// Add The Victory/Death Screen Player Input
	auto deathScreenInputGO = std::make_shared<dae::GameObject>();
	deathScreenInputGO->AddComponent(new VictoryDeathScreenInput(deathScreenGO));
	deathScreenScene.Add(deathScreenInputGO);
}

void LoadVictoryScreenSolo()
{
	// Create Scene
	auto& victoryScene = dae::SceneManager::GetInstance().CreateScene("VictorySceneSolo");

	// Add All Needed Game Objects
	victoryScene.Add(MakeVictoryScreenSoloVisuals());
	const auto victoryScreenGO = MakeVictoryDeathScreenLogic(0, g_QBertGOs[0]->GetComponent<QBert>());
	victoryScene.Add(victoryScreenGO);

	// Add The Victory/Death Screen Player Input
	auto menuPlayerInputGO = std::make_shared<dae::GameObject>();
	menuPlayerInputGO->AddComponent(new VictoryDeathScreenInput(victoryScreenGO));
	victoryScene.Add(menuPlayerInputGO);
}

void LoadDeathScreenVersus()
{
	// Create Scene
	auto& deathScreenScene = dae::SceneManager::GetInstance().CreateScene("DeathScreenVersus");

	// Add All Needed Game Objects
	deathScreenScene.Add(MakeDeathScreenVersusVisuals());
	const auto deathScreenGO = MakeVictoryDeathScreenLogic(0, g_QBertGOs[0]->GetComponent<QBert>());
	deathScreenScene.Add(deathScreenGO);

	// Add The Victory/Death Screen Player Input
	auto deathScreenInputGO = std::make_shared<dae::GameObject>();
	deathScreenInputGO->AddComponent(new VictoryDeathScreenInput(deathScreenGO));
	deathScreenScene.Add(deathScreenInputGO);
}

void LoadVictoryScreenVersus()
{
	// Create Scene
	auto& victoryScene = dae::SceneManager::GetInstance().CreateScene("VictorySceneVersus");

	// Add All Needed Game Objects
	victoryScene.Add(MakeVictoryScreenVersusVisuals());
	const auto victoryScreenGO = MakeVictoryDeathScreenLogic(0, g_QBertGOs[0]->GetComponent<QBert>());
	victoryScene.Add(victoryScreenGO);

	// Add The Victory/Death Screen Player Input
	auto menuPlayerInputGO = std::make_shared<dae::GameObject>();
	menuPlayerInputGO->AddComponent(new VictoryDeathScreenInput(victoryScreenGO));
	victoryScene.Add(menuPlayerInputGO);
}