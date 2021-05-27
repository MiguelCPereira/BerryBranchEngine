#include "Factory.h"
#include "GameObject.h"
#include "GraphicsComponent.h"
#include "LevelSectionObserver.h"
#include "SlickSam.h"
#include "QBert.h"
#include "UggWrongway.h"
#include "ResourceManager.h"
#include "FPSComponent.h"
#include "JumpingObserver.h"
#include "LivesDisplay.h"
#include "RoundLvlDisplay.h"
#include "TextComponent.h"
#include "ScoreDisplay.h"
#include "Coily.h"
#include "Disk.h"

std::vector<std::shared_ptr<dae::GameObject>> MakeQBert()
{
	const auto cursesWidth = 55.f;
	const auto cursesHeight = 29.f;
	
	const auto actualWidth = 40.f;
	const auto actualHeight = 39.f;
	const auto spriteWidth = 17.f;
	const auto spriteHeight = 16.f;
	const auto initialPosX = g_MapCenterX - actualWidth / 2.f;

	auto cursesGO = std::make_shared<dae::GameObject>();
	cursesGO->AddComponent(new dae::GraphicsComponent("QBert Curses.png", -50, -50, cursesWidth, cursesHeight));

	auto qBertGO = std::make_shared<dae::GameObject>();
	qBertGO->AddComponent(new QBert(qBertGO, cursesGO, g_NrRows, spriteWidth, spriteHeight));
	qBertGO->AddComponent(new dae::GraphicsComponent("QBert Spritesheet.png", initialPosX, g_InitialQbertPosY,
		actualWidth, actualHeight, spriteWidth * 2, 0, spriteWidth, spriteHeight));
	qBertGO->AddComponent(new JumpingObserver(qBertGO->GetComponent<QBert>(), qBertGO->GetComponent<dae::GraphicsComponent>(),
		g_CubesActualWidth, g_CubesActualHeight));

	auto livesDisplayGO = std::make_shared<dae::GameObject>();
	livesDisplayGO->AddComponent(new LivesDisplay(qBertGO->GetComponent<QBert>()));

	auto scoreDisplayGO = std::make_shared<dae::GameObject>();
	scoreDisplayGO->AddComponent(new ScoreDisplay(qBertGO->GetComponent<QBert>()));
	
	std::vector< std::shared_ptr<dae::GameObject>> returnVector;
	returnVector.push_back(std::move(qBertGO));
	returnVector.push_back(std::move(cursesGO));
	returnVector.push_back(std::move(livesDisplayGO));
	returnVector.push_back(std::move(scoreDisplayGO));
	
	return returnVector;
}


std::shared_ptr<dae::GameObject> MakeCoily(QBert* qBertComp, bool isLeft, float  moveInterval)
{
	const auto spriteWidth = 16.f;
	const auto spriteHeight = 32.f;
	const auto actualWidth = 32.f;
	const auto actualHeight = 64.f;

	auto newGO = std::make_shared<dae::GameObject>();

	if (isLeft)
	{
		newGO->AddComponent(new Coily(newGO, qBertComp, g_NrRows, g_CubesActualWidth, g_CubesActualHeight,
			spriteWidth, spriteHeight, 2, moveInterval));
		newGO->AddComponent(new dae::GraphicsComponent("Coily Spritesheet.png", g_EnemiesLeftSpawnPosX, g_EnemiesSpawnPosY - 22.f,
			actualWidth, actualHeight, 0, 0, spriteWidth, spriteHeight));
	}
	else
	{
		newGO->AddComponent(new Coily(newGO, qBertComp, g_NrRows, g_CubesActualWidth, g_CubesActualHeight,
			spriteWidth, spriteHeight, 3, moveInterval));
		newGO->AddComponent(new dae::GraphicsComponent("Coily Spritesheet.png", g_EnemiesRightSpawnPosX, g_EnemiesSpawnPosY - 22.f,
			actualWidth, actualHeight, 0, 0, spriteWidth, spriteHeight));
	}

	newGO->AddComponent(new JumpingObserver(newGO->GetComponent<Coily>(), newGO->GetComponent<dae::GraphicsComponent>(),
		g_CubesActualWidth, g_CubesActualHeight));
	newGO->GetComponent<JumpingObserver>()->Initialize();

	return newGO;
}


std::shared_ptr<dae::GameObject> MakeSlickSam(bool isSlick, bool isLeft, float  moveInterval)
{
	const auto spriteWidth = 12.f;
	const auto spriteHeight = 16.f;
	const auto actualWidth = 28.f;
	const auto actualHeight = 33.f;

	auto newGO = std::make_shared<dae::GameObject>();
	
	if (isSlick)
	{
		if (isLeft)
		{
			newGO->AddComponent(new SlickSam(newGO, g_NrRows, g_CubesActualWidth, g_CubesActualHeight,
				spriteWidth, spriteHeight, 2, moveInterval, true));
			newGO->AddComponent(new dae::GraphicsComponent("Slick Sam Spritesheet.png", g_EnemiesLeftSpawnPosX,g_EnemiesSpawnPosY,
				actualWidth, actualHeight, 0, 0, spriteWidth, spriteHeight));
		}
		else
		{
			newGO->AddComponent(new SlickSam(newGO, g_NrRows, g_CubesActualWidth, g_CubesActualHeight,
				spriteWidth, spriteHeight, 3, moveInterval, true));
			newGO->AddComponent(new dae::GraphicsComponent("Slick Sam Spritesheet.png", g_EnemiesRightSpawnPosX, g_EnemiesSpawnPosY,
				actualWidth, actualHeight, 0, 0, spriteWidth, spriteHeight));
		}
	}
	else
	{
		if (isLeft)
		{
			newGO->AddComponent(new SlickSam(newGO, g_NrRows, g_CubesActualWidth, g_CubesActualHeight,
				spriteWidth, spriteHeight, 2, moveInterval, false));
			newGO->AddComponent(new dae::GraphicsComponent("Slick Sam Spritesheet.png", g_EnemiesLeftSpawnPosX, g_EnemiesSpawnPosY,
				actualWidth, actualHeight, spriteWidth, spriteHeight, spriteWidth, spriteHeight));
		}
		else
		{
			newGO->AddComponent(new SlickSam(newGO, g_NrRows, g_CubesActualWidth, g_CubesActualHeight,
				spriteWidth, spriteHeight, 3, moveInterval, false));
			newGO->AddComponent(new dae::GraphicsComponent("Slick Sam Spritesheet.png", g_EnemiesRightSpawnPosX, g_EnemiesSpawnPosY,
				actualWidth, actualHeight, spriteWidth, spriteHeight, spriteWidth, spriteHeight));
		}
	}
	
	newGO->AddComponent(new JumpingObserver(newGO->GetComponent<SlickSam>(), newGO->GetComponent<dae::GraphicsComponent>(),
		g_CubesActualWidth, g_CubesActualHeight));
	newGO->GetComponent<JumpingObserver>()->Initialize();
	
	return newGO;
}


std::shared_ptr<dae::GameObject> MakeUggWrongway(bool isUgg, bool isLeft, float  moveInterval)
{
	const auto spriteWidth = 16.f;
	const auto spriteHeight = 16.f;
	const auto actualWidth = 30.f;
	const auto actualHeight = 30.f;
	const auto leftSpawnPositionX = 100.f;
	const auto rightSpawnPositionX = 535.f;
	const auto spawnPositionY = 400.f;

	auto newGO = std::make_shared<dae::GameObject>();

	if (isUgg)
	{
		if (isLeft)
		{
			newGO->AddComponent(new UggWrongway(newGO, g_NrRows, g_CubesActualWidth, g_CubesActualHeight,
				spriteWidth, spriteHeight, 22, moveInterval, true, true));
			newGO->AddComponent(new dae::GraphicsComponent("Ugg Wrongway Spritesheet.png", leftSpawnPositionX, spawnPositionY,
				actualWidth, actualHeight, spriteWidth, 0, spriteWidth, spriteHeight));
		}
		else
		{
			newGO->AddComponent(new UggWrongway(newGO, g_NrRows, g_CubesActualWidth, g_CubesActualHeight,
				spriteWidth, spriteHeight, 28, moveInterval, true, false));
			newGO->AddComponent(new dae::GraphicsComponent("Ugg Wrongway Spritesheet.png", rightSpawnPositionX, spawnPositionY,
				actualWidth, actualHeight, spriteWidth*3, 0, spriteWidth, spriteHeight));
		}
	}
	else
	{
		if (isLeft)
		{
			newGO->AddComponent(new UggWrongway(newGO, g_NrRows, g_CubesActualWidth, g_CubesActualHeight,
				spriteWidth, spriteHeight, 22, moveInterval, false, true));
			newGO->AddComponent(new dae::GraphicsComponent("Ugg Wrongway Spritesheet.png", leftSpawnPositionX, spawnPositionY,
				actualWidth, actualHeight, spriteWidth, spriteHeight, spriteWidth, spriteHeight));
		}
		else
		{
			newGO->AddComponent(new UggWrongway(newGO, g_NrRows, g_CubesActualWidth, g_CubesActualHeight,
				spriteWidth, spriteHeight, 28, moveInterval, false, false));
			newGO->AddComponent(new dae::GraphicsComponent("Ugg Wrongway Spritesheet.png", rightSpawnPositionX, spawnPositionY,
				actualWidth, actualHeight, spriteWidth*3, spriteHeight, spriteWidth, spriteHeight));
		}
	}

	newGO->AddComponent(new JumpingObserver(newGO->GetComponent<UggWrongway>(), newGO->GetComponent<dae::GraphicsComponent>(),
		g_CubesActualWidth, g_CubesActualHeight));
	newGO->GetComponent<JumpingObserver>()->Initialize();

	return newGO;
}


std::shared_ptr<dae::GameObject> MakeLevelTitle(int lvlNr)
{
	const auto width = 500.f;
	const auto height = 230.f;
	const auto positionX = 78.f;
	const auto positionY = 150.f;

	auto newGO = std::make_shared<dae::GameObject>();

	if (lvlNr == 1)
		newGO->AddComponent(new dae::GraphicsComponent("Level 01 Title.png", positionX, positionY, width, height));
	else if (lvlNr == 2)
		newGO->AddComponent(new dae::GraphicsComponent("Level 02 Title.png", positionX, positionY, width, height));
	else
		newGO->AddComponent(new dae::GraphicsComponent("Level 03 Title.png", positionX, positionY, width, height));

	return newGO;
}


std::shared_ptr<dae::GameObject> MakeLevelTransition(QBert* qBertComp)
{
	const float transitionTime = 2.f;

	auto sectionObserverGO = std::make_shared<dae::GameObject>();
	sectionObserverGO->AddComponent(new LevelSectionObserver(transitionTime, qBertComp));

	return sectionObserverGO;
}


std::shared_ptr<dae::GameObject> MakeVictoryTitle()
{
	const auto width = 474.f;
	const auto height = 263.f;
	const auto positionX = 86.f;
	const auto positionY = 90.f;

	auto newGO = std::make_shared<dae::GameObject>();
	newGO->AddComponent(new dae::GraphicsComponent("Victory Title.png", positionX, positionY, width, height));

	return newGO;
}


std::shared_ptr<dae::GameObject> MakeFPSCounter()
{
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 19);
	auto fpsCounterGO = std::make_shared<dae::GameObject>();
	fpsCounterGO->AddComponent(new dae::FPSComponent(fpsCounterGO));
	fpsCounterGO->AddComponent(new dae::TextComponent("FAIL FPS", font, 255, 255, 0));
	fpsCounterGO->GetComponent<dae::TextComponent>()->SetPosition(10, 10);

	return fpsCounterGO;
}


std::shared_ptr<dae::GameObject> MakeHeartForDisplay(bool playerOne, float posY)
{
	const auto width = 30;
	const auto height = 28;
	float posX;
	
	if (playerOne)
		posX = 20.f;
	else
		posX = 590.f;

	auto heartGO = std::make_shared<dae::GameObject>();
	heartGO->AddComponent(new dae::GraphicsComponent("Heart.png", posX, posY, width, height));

	return heartGO;
}


std::shared_ptr<dae::GameObject> MakeScoreDisplay(bool playerOne)
{
	const auto titleActualWidth = 195;
	const auto titleActualHeight = 33;
	const auto titleSpriteWidth = 65;
	const auto titleSpriteHeight = 11;
	const auto posYPlayerTitle = 20.f;
	const auto posYScore = 80.f;
	float posX;

	if (playerOne)
		posX = 20.f;
	else
		posX = 420.f;

	auto scoreGO = std::make_shared<dae::GameObject>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Minecraft.ttf", 23);
	scoreGO->AddComponent(new dae::TextComponent("SCORE: FAIL", font, 237, 164, 69));
	scoreGO->GetComponent<dae::TextComponent>()->SetPosition(posX, posYScore);
	scoreGO->AddComponent(new dae::GraphicsComponent("Player Titles.png", posX, posYPlayerTitle, 
		titleActualWidth, titleActualHeight, 0, 0, titleSpriteWidth, titleSpriteHeight));

	return scoreGO;
}


std::shared_ptr<dae::GameObject> MakeLevelDisplay(bool coOpOn)
{
	float posY;
	float posX;

	if (coOpOn)
	{
		posX = 230.f;
		posY = 445.f;
	}
	else
	{
		posX = 530.f;
		posY = 80.f;
	}

	auto levelGO = std::make_shared<dae::GameObject>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Minecraft.ttf", 19);
	levelGO->AddComponent(new dae::TextComponent("LEVEL: 0", font, 237, 164, 69));
	levelGO->GetComponent<dae::TextComponent>()->SetPosition(posX, posY);
	

	return levelGO;
}


std::shared_ptr<dae::GameObject> MakeRoundDisplay(bool coOpOn)
{
	float posY;
	float posX;

	if (coOpOn)
	{
		posX = 350.f;
		posY = 445.f;
	}
	else
	{
		posX = 529.f;
		posY = 120.f;
	}

	auto roundGO = std::make_shared<dae::GameObject>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Minecraft.ttf", 19);
	roundGO->AddComponent(new dae::TextComponent("ROUND: 0", font, 237, 164, 69));
	roundGO->GetComponent<dae::TextComponent>()->SetPosition(posX, posY);

	return roundGO;
}


std::shared_ptr<dae::GameObject> MakeRoundLevelDisplayGO(QBert* qBertComp, bool coOpOn)
{
	auto displayGO = std::make_shared<dae::GameObject>();
	displayGO->AddComponent(new RoundLvlDisplay(qBertComp, coOpOn));
	return displayGO;
}


std::shared_ptr<dae::GameObject> MakeDiskGO(int row, bool isLeft, int colorIdx)
{
	const auto actualWidth = 32.f;
	const auto actualHeight = 20.f;
	const auto spriteWidth = 16.f;
	const auto spriteHeight = 10.f;
	const auto topFinalPosY = g_DiskTopRowY;
	const auto topFinalPosX = g_MapCenterX - actualWidth / 2.f;
	const auto posY = g_DiskTopRowY + g_CubesActualHeight * 0.75f * float(row - 1);
	float posX = g_MapCenterX;

	if (isLeft)
		posX -= g_CubesActualWidth / 2.f * float(row) + actualWidth / 2.f;
	else
		posX += g_CubesActualWidth / 2.f * float(row) - actualWidth / 2.f;
	
	auto diskGO = std::make_shared<dae::GameObject>();
	diskGO->AddComponent(new dae::GraphicsComponent("Disk Spritesheet.png", posX, posY,
		actualWidth, actualHeight, 0, 0, spriteWidth, spriteHeight));
	diskGO->AddComponent(new Disk(diskGO, row, isLeft, colorIdx, topFinalPosX, topFinalPosY, g_InitialQbertPosY, spriteWidth, spriteHeight));
	return diskGO;
}

std::vector<std::shared_ptr<dae::GameObject>>* MakeDiskGOsVector(int level, int colorIdx)
{
	auto* diskGOsVector = new std::vector<std::shared_ptr<dae::GameObject>>();

	std::vector<int> freeRowsLeft;
	std::vector<int> freeRowsRight;

	for(auto i = 0; i < g_NrRows; i++)
	{
		freeRowsLeft.push_back(i + 1);
		freeRowsRight.push_back(i + 1);
	}
	
	// Make left disk
	int row = freeRowsLeft[rand() % int(freeRowsLeft.size())];
	auto diskGO = MakeDiskGO(row, true, colorIdx);
	diskGOsVector->push_back(std::move(diskGO));
	freeRowsLeft.erase(std::find(freeRowsLeft.begin(), freeRowsLeft.end(), row));

	// Make right disk
	row = freeRowsRight[rand() % int(freeRowsRight.size())];
	diskGO = MakeDiskGO(row, false, colorIdx);
	diskGOsVector->push_back(std::move(diskGO));
	freeRowsRight.erase(std::find(freeRowsRight.begin(), freeRowsRight.end(), row));

	if(level != 1)
	{
		// Make one more right disk
		row = freeRowsRight[rand() % int(freeRowsRight.size())];
		diskGO = MakeDiskGO(row, false, colorIdx);
		diskGOsVector->push_back(std::move(diskGO));
		// No need to erase from the vector, as it is certain no more disks are gonna be created on the right

		if (level == 3)
		{
			// Make one more left disk
			row = freeRowsLeft[rand() % int(freeRowsLeft.size())];
			diskGO = MakeDiskGO(row, true, colorIdx);
			diskGOsVector->push_back(std::move(diskGO));
			// No need to erase from the vector, as it is certain no more disks are gonna be created on the left
		}
	}

	return diskGOsVector;
}
