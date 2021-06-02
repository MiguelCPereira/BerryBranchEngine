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
#include "SoloVersusP1Input.h"
#include "VictoryDeathScreenInput.h"
#include "GraphicsComponent.h"

// To create and read binary files
#include<fstream>

#include "CoopAllInput.h"


// Global Variables

const int g_CubesSpriteHeight = 32;
const int g_CubesSpriteWidth = 32;
const float g_PyramidPosX = 300.f;
const float g_PyramidPosY = 80.f;

const float g_CoopP1SpawnPosX = g_MapCenterX - g_CubesActualWidth * 3.f - g_QBertActualWidth / 2.f;
const float g_CoopP2SpawnPosX = g_MapCenterX + g_CubesActualWidth * 3.f - g_QBertActualWidth / 2.f;
const float g_CoopSpawnPosY = g_InitialQbertPosY + g_CubesActualHeight * 0.75f * 6.f;

std::vector<std::shared_ptr<dae::GameObject>> g_QBertP1GOs;
std::vector<std::shared_ptr<dae::GameObject>> g_QBertP2GOs;
auto* g_QBertsCompVector = new std::vector<QBert*>();
auto* g_QBertsGraphicsVector = new std::vector<dae::GraphicsComponent*>();


// Global Functions
void SetUpQBerts();
void PrintInstructions();

void LoadStartScreen();
void LoadDeathScreenSolo();
void LoadVictoryScreenSolo();
void LoadDeathScreenCoop();
void LoadVictoryScreenCoop();
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

	SetUpQBerts();
	LoadStartScreen(); // Scene idx 00
	
	LoadDeathScreenSolo(); // Scene idx 01
	LoadLevelsBinaries("Level01Solo.bin"); // Scene idx 02-06
	LoadLevelsBinaries("Level02Solo.bin"); // Scene idx 07-11
	LoadLevelsBinaries("Level03Solo.bin"); // Scene idx 12-16
	LoadVictoryScreenSolo(); // Scene idx 17
	
	LoadDeathScreenCoop(); // Scene idx 18
	LoadLevelsBinaries("Level01Coop.bin"); // Scene idx 19-23
	LoadLevelsBinaries("Level02Coop.bin"); // Scene idx 24-28
	LoadLevelsBinaries("Level03Coop.bin"); // Scene idx 29-33
	LoadVictoryScreenCoop(); // Scene idx 34
	
	LoadDeathScreenVersus(); // Scene idx 35
	LoadLevelsBinaries("Level01Versus.bin"); // Scene idx 36-40
	LoadLevelsBinaries("Level02Versus.bin"); // Scene idx 41-45
	LoadLevelsBinaries("Level03Versus.bin"); // Scene idx 46-50
	LoadVictoryScreenVersus(); // Scene idx 51
	
	PrintInstructions();

	engine.Run();

	return 0;
}





void SetUpQBerts()
{
	g_QBertP1GOs = MakeQBert(true);
	g_QBertP2GOs = MakeQBert(false);
	g_QBertsCompVector->push_back(g_QBertP1GOs[0]->GetComponent<QBert>());
	g_QBertsCompVector->push_back(g_QBertP2GOs[0]->GetComponent<QBert>());
	g_QBertsGraphicsVector->push_back(g_QBertP1GOs[0]->GetComponent<dae::GraphicsComponent>());
	g_QBertsGraphicsVector->push_back(g_QBertP2GOs[0]->GetComponent<dae::GraphicsComponent>());
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
		std::cout << "Level file '" << fileName << "' couldn't be opened\n";

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
	else if (rounds[0].gameMode == 2)
		levelTitleSceneName += "Coop";
	else
		levelTitleSceneName += "Versus";

	auto& levelTitleScene = dae::SceneManager::GetInstance().CreateScene(levelTitleSceneName);

	// Add All Needed Game Objects
	levelTitleScene.Add(MakeLevelTitle(rounds[0].level, rounds[0].gameMode));
	levelTitleScene.Add(MakeLevelTransition(g_QBertsCompVector, rounds[0].gameMode));



	//// Create A Scene And Fill It Properly For Each Round

	for (const auto& round : rounds)
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

		// Transfer QBert(s)
		for (const auto& gameObject : g_QBertP1GOs)
			scene.Add(gameObject);

		if (round.gameMode == 2)
		{
			for (const auto& gameObject : g_QBertP2GOs)
				scene.Add(gameObject);
		}

		// Make UI
		std::vector<std::shared_ptr<dae::GameObject>> uiGOs;

		if (round.gameMode == 2)
			uiGOs = MakeUI(g_QBertsCompVector, true);
		else
			uiGOs = MakeUI(g_QBertsCompVector, false);

		for (const auto& gameObject : uiGOs)
			scene.Add(gameObject);

		// Level Section Observer
		int deathSceneIdx;
		if (round.gameMode == 1) // Solo
			deathSceneIdx = 1;
		else if (round.gameMode == 2) // Co-op
			deathSceneIdx = 18;
		else					// Versus
			deathSceneIdx = 35;

		auto sectionObserverGO = std::make_shared<dae::GameObject>();
		sectionObserverGO->AddComponent(new LevelSectionObserver(sectionObserverGO, g_QBertsCompVector, g_QBertsGraphicsVector, pyramid, disksVector, deathSceneIdx, round.level,
			round.gameMode, g_CoopP1SpawnPosX, g_CoopP2SpawnPosX, g_CoopSpawnPosY,
			round.spawnSlickSams, round.spawnUggWrongs, round.slickSamsSpawnInterval, round.uggWrongSpawnInterval));

		scene.Add(sectionObserverGO);

		// Add The Mode's Player Input
		auto gamePlayerInputGO = std::make_shared<dae::GameObject>();

		if (round.gameMode == 2)
			gamePlayerInputGO->AddComponent(new CoopAllInput(g_QBertP1GOs[0], g_QBertP2GOs[0]));
		else
			gamePlayerInputGO->AddComponent(new SoloVersusP1Input(g_QBertP1GOs[0]));

		scene.Add(gamePlayerInputGO);
	}
}





void LoadStartScreen()
{
	// Create Scene
	auto& startScreenScene = dae::SceneManager::GetInstance().CreateScene("StartScreen");

	// Add All Needed Game Objects
	startScreenScene.Add(MakeStartScreenVisuals());
	const auto startScreenGO = MakeStartScreenLogic(2, 19, 36);
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
	const auto deathScreenGO = MakeOneQbertVictoryDeathScreenLogic(0, g_QBertP1GOs[0]->GetComponent<QBert>());
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
	const auto victoryScreenGO = MakeOneQbertVictoryDeathScreenLogic(0, g_QBertP1GOs[0]->GetComponent<QBert>());
	victoryScene.Add(victoryScreenGO);

	// Add The Victory/Death Screen Player Input
	auto menuPlayerInputGO = std::make_shared<dae::GameObject>();
	menuPlayerInputGO->AddComponent(new VictoryDeathScreenInput(victoryScreenGO));
	victoryScene.Add(menuPlayerInputGO);
}

void LoadDeathScreenCoop()
{
	// Create Scene
	auto& deathScreenScene = dae::SceneManager::GetInstance().CreateScene("DeathScreenCoop");

	// Add All Needed Game Objects
	deathScreenScene.Add(MakeDeathScreenCoopVisuals());
	const auto deathScreenGO = MakeTwoQbertsVictoryDeathScreenLogic(0, g_QBertsCompVector);
	deathScreenScene.Add(deathScreenGO);

	// Add The Victory/Death Screen Player Input
	auto deathScreenInputGO = std::make_shared<dae::GameObject>();
	deathScreenInputGO->AddComponent(new VictoryDeathScreenInput(deathScreenGO));
	deathScreenScene.Add(deathScreenInputGO);
}

void LoadVictoryScreenCoop()
{
	// Create Scene
	auto& victoryScene = dae::SceneManager::GetInstance().CreateScene("VictorySceneCoop");

	// Add All Needed Game Objects
	victoryScene.Add(MakeVictoryScreenCoopVisuals());
	const auto victoryScreenGO = MakeTwoQbertsVictoryDeathScreenLogic(0, g_QBertsCompVector);
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
	const auto deathScreenGO = MakeOneQbertVictoryDeathScreenLogic(0, g_QBertP1GOs[0]->GetComponent<QBert>());
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
	const auto victoryScreenGO = MakeOneQbertVictoryDeathScreenLogic(0, g_QBertP1GOs[0]->GetComponent<QBert>());
	victoryScene.Add(victoryScreenGO);

	// Add The Victory/Death Screen Player Input
	auto menuPlayerInputGO = std::make_shared<dae::GameObject>();
	menuPlayerInputGO->AddComponent(new VictoryDeathScreenInput(victoryScreenGO));
	victoryScene.Add(menuPlayerInputGO);
}