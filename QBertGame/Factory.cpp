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
#include "MenuScoreDisplay.h"
#include "StartScreen.h"
#include "VictoryDeathScreen.h"

std::vector<std::shared_ptr<dae::GameObject>> MakeQBert(bool playerOne)
{
	const auto cursesWidth = 55.f;
	const auto cursesHeight = 29.f;
	
	const auto actualHeight = 39.f;
	const auto spriteWidth = 17.f;
	const auto spriteHeight = 16.f;
	const auto initialPosX = g_MapCenterX - g_QBertActualWidth / 2.f;

	auto cursesGO = std::make_shared<dae::GameObject>();
	cursesGO->AddComponent(new dae::GraphicsComponent("QBert Curses.png", -50, -50, cursesWidth, cursesHeight));

	auto qBertGO = std::make_shared<dae::GameObject>();
	qBertGO->AddComponent(new QBert(qBertGO, cursesGO, g_NrRows, spriteWidth, spriteHeight, playerOne));

	if (playerOne)
	{
		qBertGO->AddComponent(new dae::GraphicsComponent("QBert Spritesheet.png", initialPosX, g_InitialQbertPosY,
			g_QBertActualWidth, actualHeight, spriteWidth * 2, 0, spriteWidth, spriteHeight));
	}
	else
	{
		qBertGO->AddComponent(new dae::GraphicsComponent("QBert Spritesheet.png", initialPosX, g_InitialQbertPosY,
			g_QBertActualWidth, actualHeight, spriteWidth * 3, 0, spriteWidth, spriteHeight));
	}
	
	qBertGO->AddComponent(new JumpingObserver(qBertGO->GetComponent<QBert>(), qBertGO->GetComponent<dae::GraphicsComponent>(),
		g_CubesActualWidth, g_CubesActualHeight));

	std::vector< std::shared_ptr<dae::GameObject>> returnVector;
	returnVector.push_back(std::move(qBertGO));
	returnVector.push_back(std::move(cursesGO));
	
	return returnVector;
}


std::shared_ptr<dae::GameObject> MakeCoily(std::vector<QBert*>* qBertCompVector, bool isLeft, float  moveInterval, int gameMode)
{
	const auto spriteWidth = 16.f;
	const auto spriteHeight = 32.f;
	const auto actualWidth = 32.f;
	const auto actualHeight = 64.f;

	auto newGO = std::make_shared<dae::GameObject>();

	if (isLeft)
	{
		newGO->AddComponent(new Coily(newGO, qBertCompVector, gameMode, g_NrRows, g_CubesActualWidth, g_CubesActualHeight,
			spriteWidth, spriteHeight, 2, moveInterval));
		newGO->AddComponent(new dae::GraphicsComponent("Coily Spritesheet.png", g_EnemiesLeftSpawnPosX, g_EnemiesSpawnPosY - 22.f,
			actualWidth, actualHeight, 0, 0, spriteWidth, spriteHeight));
	}
	else
	{
		newGO->AddComponent(new Coily(newGO, qBertCompVector, gameMode, g_NrRows, g_CubesActualWidth, g_CubesActualHeight,
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


///


std::shared_ptr<dae::GameObject> MakeLevelTitle(int lvlNr, int gameMode)
{
	const auto width = 500.f;
	const auto height = 230.f;
	const auto titlePosX = 78.f;
	const auto titlePosY = 90.f;
	const auto subTitlePosX = 235.f;
	const auto subTitlePosY = 360.f;

	
	auto newGO = std::make_shared<dae::GameObject>();

	
	if (lvlNr == 1)
		newGO->AddComponent(new dae::GraphicsComponent("Level 01 Title.png", titlePosX, titlePosY, width, height));
	else if (lvlNr == 2)
		newGO->AddComponent(new dae::GraphicsComponent("Level 02 Title.png", titlePosX, titlePosY, width, height));
	else
		newGO->AddComponent(new dae::GraphicsComponent("Level 03 Title.png", titlePosX, titlePosY, width, height));

	
	auto font = dae::ResourceManager::GetInstance().LoadFont("Minecraft.ttf", 40);
	
	if (gameMode == 1)
	{
		newGO->AddComponent(new dae::TextComponent("Solo Mode", font, 219, 184, 125));
		newGO->GetComponent<dae::TextComponent>()->SetPosition(subTitlePosX, subTitlePosY);
	}
	else if (gameMode == 2)
	{
		newGO->AddComponent(new dae::TextComponent("Co-op Mode", font, 219, 184, 125));
		newGO->GetComponent<dae::TextComponent>()->SetPosition(subTitlePosX - 20.f, subTitlePosY);
	}
	else
	{
		newGO->AddComponent(new dae::TextComponent("Versus Mode", font, 219, 184, 125));
		newGO->GetComponent<dae::TextComponent>()->SetPosition(subTitlePosX - 30.f, subTitlePosY);
	}

	
	return newGO;
}


std::shared_ptr<dae::GameObject> MakeLevelTransition(std::vector<QBert*>* qBertCompVector, int gameMode)
{
	const float transitionTime = 2.f;

	auto sectionObserverGO = std::make_shared<dae::GameObject>();
	sectionObserverGO->AddComponent(new LevelSectionObserver(transitionTime, qBertCompVector, gameMode));

	return sectionObserverGO;
}


///


std::shared_ptr<dae::GameObject> MakeFPSCounter()
{
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 19);
	auto fpsCounterGO = std::make_shared<dae::GameObject>();
	fpsCounterGO->AddComponent(new dae::FPSComponent(fpsCounterGO));
	fpsCounterGO->AddComponent(new dae::TextComponent("FAIL FPS", font, 255, 255, 0));
	fpsCounterGO->GetComponent<dae::TextComponent>()->SetPosition(10, 10);

	return fpsCounterGO;
}


///


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


std::vector<std::shared_ptr<dae::GameObject>>* MakeLivesDisplayVisuals(bool playerOne, int livesAmount)
{
	auto posY = 130.f;
	auto spacingBetweenHearts = 40.f;

	auto* returnVector = new std::vector< std::shared_ptr<dae::GameObject>>();
	
	for (auto i = 0; i < livesAmount; i++)
	{
		auto heartGO = MakeHeartForDisplay(playerOne, posY);
		posY += spacingBetweenHearts;
		returnVector->push_back(std::move(heartGO));
	}

	return returnVector;
}


std::shared_ptr<dae::GameObject> MakeScoreDisplayVisuals(bool playerOne)
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

	if (playerOne)
	{
		scoreGO->AddComponent(new dae::GraphicsComponent("Player Titles.png", posX, posYPlayerTitle,
			titleActualWidth, titleActualHeight, 0, 0, titleSpriteWidth, titleSpriteHeight));
	}
	else
	{
		scoreGO->AddComponent(new dae::GraphicsComponent("Player Titles.png", posX, posYPlayerTitle,
			titleActualWidth, titleActualHeight, 0, titleSpriteHeight, titleSpriteWidth, titleSpriteHeight));
	}

	return scoreGO;
}


std::shared_ptr<dae::GameObject> MakeLevelDisplayVisuals(bool coOpOn)
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


std::shared_ptr<dae::GameObject> MakeRoundDisplayVisuals(bool coOpOn)
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


std::vector<std::shared_ptr<dae::GameObject>> MakeUI(std::vector<QBert*>* qBertCompVector, bool coOpOn)
{
	std::vector< std::shared_ptr<dae::GameObject>> returnVector;


	
	// Make the Level/Round Display
	auto levelVisualsGO = MakeLevelDisplayVisuals(coOpOn);
	auto roundVisualsGO = MakeRoundDisplayVisuals(coOpOn);
	auto roundLevelGO = std::make_shared<dae::GameObject>();
	roundLevelGO->AddComponent(new RoundLvlDisplay(qBertCompVector->operator[](0), coOpOn, levelVisualsGO->GetComponent<dae::TextComponent>(),
		roundVisualsGO->GetComponent<dae::TextComponent>()));
	returnVector.push_back(std::move(levelVisualsGO));
	returnVector.push_back(std::move(roundVisualsGO));
	returnVector.push_back(std::move(roundLevelGO));
	

	
	// Make the Lives Display
	auto* heartsGOVector1 = MakeLivesDisplayVisuals(true, qBertCompVector->operator[](0)->GetMaxLives());
	auto* graphicsCompVector1 = new std::vector<dae::GraphicsComponent*>();
	
	for(size_t i = 0; i < heartsGOVector1->size(); i++)
	{
		graphicsCompVector1->push_back(heartsGOVector1->operator[](i)->GetComponent<dae::GraphicsComponent>());
		returnVector.push_back(std::move(heartsGOVector1->operator[](i)));
	}
	
	auto livesGO1 = std::make_shared<dae::GameObject>();
	livesGO1->AddComponent(new LivesDisplay(qBertCompVector->operator[](0), graphicsCompVector1));
	returnVector.push_back(std::move(livesGO1));


	
	// Make the Score Display
	auto scoreGO1 = MakeScoreDisplayVisuals(true);
	scoreGO1->AddComponent(new ScoreDisplay(qBertCompVector->operator[](0), scoreGO1->GetComponent<dae::TextComponent>()));
	returnVector.push_back(std::move(scoreGO1));


	
	// If there's co-op, make another pair of score and lives displays
	if (coOpOn)
	{
		auto* heartsGOVector2 = MakeLivesDisplayVisuals(false, qBertCompVector->operator[](1)->GetMaxLives());
		auto* graphicsCompVector2 = new std::vector<dae::GraphicsComponent*>();

		for (size_t i = 0; i < heartsGOVector1->size(); i++)
		{
			graphicsCompVector2->push_back(heartsGOVector2->operator[](i)->GetComponent<dae::GraphicsComponent>());
			returnVector.push_back(std::move(heartsGOVector2->operator[](i)));
		}
		
		auto livesGO2 = std::make_shared<dae::GameObject>();
		livesGO2->AddComponent(new LivesDisplay(qBertCompVector->operator[](1), graphicsCompVector2));
		returnVector.push_back(std::move(livesGO2));

		
		auto scoreGO2 = MakeScoreDisplayVisuals(false);
		scoreGO2->AddComponent(new ScoreDisplay(qBertCompVector->operator[](1), scoreGO2->GetComponent<dae::TextComponent>()));
		returnVector.push_back(std::move(scoreGO2));
	}


	
	return returnVector;
}


///


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



///


std::shared_ptr<dae::GameObject> MakeStartScreenVisuals()
{
	const auto titlePosX = 75.f;
	const auto titlePosY = 80.f;
	const auto buttonDistance = 40.f;
	const auto buttonsPosY = 300.f;
	const auto buttonsPosX = 235.f;


	auto buttonsGO = std::make_shared<dae::GameObject>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Minecraft.ttf", 30);
	
	auto soloButtonComp = new dae::TextComponent("Solo Mode", font, 255, 216, 102);
	soloButtonComp->SetPosition(buttonsPosX + 20, buttonsPosY);
	buttonsGO->AddComponent(soloButtonComp);

	auto coopButtonComp = new dae::TextComponent("Co-op Mode", font, 255, 216, 102);
	coopButtonComp->SetPosition(buttonsPosX + 6, buttonsPosY + buttonDistance);
	buttonsGO->AddComponent(coopButtonComp);

	auto versusButtonComp = new dae::TextComponent("Versus Mode", font, 255, 216, 102);
	versusButtonComp->SetPosition(buttonsPosX, buttonsPosY + buttonDistance * 2);
	buttonsGO->AddComponent(versusButtonComp);
	
	auto titleComp = new dae::GraphicsComponent("Game Title.png", titlePosX, titlePosY);
	buttonsGO->AddComponent(titleComp);
	
	return buttonsGO;
}


std::shared_ptr<dae::GameObject> MakeStartScreenLogic(int soloModeSceneIdx, int coopModeSceneIdx, int versusModeSceneIdx)
{
	const auto actualWidth = 18.f;
	const auto actualHeight = 27.f;
	const auto posX = 205.f;
	const auto posY = 298.f;
	const auto buttonDistance = 40.f;

	auto startScreenGO = std::make_shared<dae::GameObject>();
	const auto selectionGraphics = new dae::GraphicsComponent("Selection Arrow.png", posX, posY, actualWidth, actualHeight);
	startScreenGO->AddComponent(selectionGraphics);
	startScreenGO->AddComponent(new StartScreen(soloModeSceneIdx, coopModeSceneIdx, versusModeSceneIdx, selectionGraphics, buttonDistance));

	return startScreenGO;
}



///


std::shared_ptr<dae::GameObject> MakeVictoryScreenSoloVisuals()
{
	const auto width = 270.f;
	const auto height = 149.f;
	const auto titlePosX = 183.f;
	const auto titlePosY = 30.f;
	const auto scoreTextPosX = 250.f;
	const auto scoreTextPosY = 240.f;
	const auto goBackPosX = 135.f;
	const auto goBackPosY = 400.f;

	auto newGO = std::make_shared<dae::GameObject>();

	// Add the title
	newGO->AddComponent(new dae::GraphicsComponent("Victory Title.png", titlePosX, titlePosY, width, height));

	// Add the score text (the "SCORE:", not the actual number)
	auto font = dae::ResourceManager::GetInstance().LoadFont("Minecraft.ttf", 38);
	auto* scoreComp = new dae::TextComponent("SCORE", font);
	scoreComp->SetPosition(scoreTextPosX, scoreTextPosY);
	newGO->AddComponent(scoreComp);

	// And add the bottom text explaining how to return to the start menu
	font = dae::ResourceManager::GetInstance().LoadFont("Minecraft.ttf", 16);
	auto* goBackComp = new dae::TextComponent("Press ESC or START to go back to the main menu", font);
	goBackComp->SetPosition(goBackPosX, goBackPosY);
	newGO->AddComponent(goBackComp);

	return newGO;
}


std::shared_ptr<dae::GameObject> MakeVictoryScreenCoopVisuals()
{
	const auto width = 270.f;
	const auto height = 149.f;
	const auto titlePosX = 183.f;
	const auto titlePosY = 30.f;
	const auto score1TextPosX = 90.f;
	const auto score2TextPosX = 350.f;
	const auto scoresTextsPosY = 240.f;
	const auto goBackPosX = 135.f;
	const auto goBackPosY = 400.f;

	auto newGO = std::make_shared<dae::GameObject>();

	// Add the title
	newGO->AddComponent(new dae::GraphicsComponent("Victory Title.png", titlePosX, titlePosY, width, height));

	// Add the P1 score text (the "P1 SCORE:", not the actual number)
	auto font = dae::ResourceManager::GetInstance().LoadFont("Minecraft.ttf", 38);
	auto* score1Comp = new dae::TextComponent("P1 SCORE", font);
	score1Comp->SetPosition(score1TextPosX, scoresTextsPosY);
	newGO->AddComponent(score1Comp);

	// Add the P2 score text (the "P2 SCORE:", not the actual number)
	auto* score2Comp = new dae::TextComponent("P2 SCORE", font);
	score2Comp->SetPosition(score2TextPosX, scoresTextsPosY);
	newGO->AddComponent(score2Comp);

	// And add the bottom text explaining how to return to the start menu
	font = dae::ResourceManager::GetInstance().LoadFont("Minecraft.ttf", 16);
	auto* goBackComp = new dae::TextComponent("Press ESC or START to go back to the main menu", font);
	goBackComp->SetPosition(goBackPosX, goBackPosY);
	newGO->AddComponent(goBackComp);

	return newGO;
}


std::shared_ptr<dae::GameObject> MakeVictoryScreenVersusVisuals()
{
	const auto titleAPosX = 170.f;
	const auto titleAPosY = 70.f;
	const auto titleBPosX = 250.f;
	const auto titleBPosY = 135.f;
	const auto scoreTextPosX = 250.f;
	const auto scoreTextPosY = 240.f;
	const auto goBackPosX = 126.f;
	const auto goBackPosY = 400.f;

	auto newGO = std::make_shared<dae::GameObject>();

	// Add the title
	auto font = dae::ResourceManager::GetInstance().LoadFont("Minecraft.ttf", 60);
	auto* titleAComp = new dae::TextComponent("PLAYER 1", font);
	titleAComp->SetPosition(titleAPosX, titleAPosY);
	newGO->AddComponent(titleAComp);
	auto* titleBComp = new dae::TextComponent("WON", font);
	titleBComp->SetPosition(titleBPosX, titleBPosY);
	newGO->AddComponent(titleBComp);

	// Add the score text (the "SCORE:", not the actual number)
	font = dae::ResourceManager::GetInstance().LoadFont("Minecraft.ttf", 38);
	auto* scoreComp = new dae::TextComponent("SCORE", font);
	scoreComp->SetPosition(scoreTextPosX, scoreTextPosY);
	newGO->AddComponent(scoreComp);

	// And add the bottom text explaining how to return to the start menu
	font = dae::ResourceManager::GetInstance().LoadFont("Minecraft.ttf", 16);
	auto* goBackComp = new dae::TextComponent("Press ESC or START to go back to the main menu", font);
	goBackComp->SetPosition(goBackPosX, goBackPosY);
	newGO->AddComponent(goBackComp);

	return newGO;
}


///


std::shared_ptr<dae::GameObject> MakeDeathScreenSoloVisuals()
{
	const auto width = 376.f;
	const auto height = 149.f;
	const auto titlePosX = 130.f;
	const auto titlePosY = 40.f;
	const auto scoreTextPosX = 250.f;
	const auto scoreTextPosY = 240.f;
	const auto goBackPosX = 126.f;
	const auto goBackPosY = 400.f;

	auto newGO = std::make_shared<dae::GameObject>();

	// Add the title
	newGO->AddComponent(new dae::GraphicsComponent("Game Over Title.png", titlePosX, titlePosY, width, height));

	// Add the score text (the "SCORE:", not the actual number)
	auto font = dae::ResourceManager::GetInstance().LoadFont("Minecraft.ttf", 38);
	auto* scoreComp = new dae::TextComponent("SCORE", font);
	scoreComp->SetPosition(scoreTextPosX, scoreTextPosY);
	newGO->AddComponent(scoreComp);

	// And add the bottom text explaining how to return to the start menu
	font = dae::ResourceManager::GetInstance().LoadFont("Minecraft.ttf", 16);
	auto* goBackComp = new dae::TextComponent("Press ESC or START to go back to the main menu", font);
	goBackComp->SetPosition(goBackPosX, goBackPosY);
	newGO->AddComponent(goBackComp);

	return newGO;
}


std::shared_ptr<dae::GameObject> MakeDeathScreenCoopVisuals()
{
	const auto width = 376.f;
	const auto height = 149.f;
	const auto titlePosX = 130.f;
	const auto titlePosY = 40.f;
	const auto score1TextPosX = 90.f;
	const auto score2TextPosX = 350.f;
	const auto scoresTextsPosY = 240.f;
	const auto goBackPosX = 126.f;
	const auto goBackPosY = 400.f;

	auto newGO = std::make_shared<dae::GameObject>();

	// Add the title
	newGO->AddComponent(new dae::GraphicsComponent("Game Over Title.png", titlePosX, titlePosY, width, height));

	// Add the P1 score text (the "P1 SCORE:", not the actual number)
	auto font = dae::ResourceManager::GetInstance().LoadFont("Minecraft.ttf", 38);
	auto* score1Comp = new dae::TextComponent("P1 SCORE", font);
	score1Comp->SetPosition(score1TextPosX, scoresTextsPosY);
	newGO->AddComponent(score1Comp);

	// Add the P2 score text (the "P2 SCORE:", not the actual number)
	auto* score2Comp = new dae::TextComponent("P2 SCORE", font);
	score2Comp->SetPosition(score2TextPosX, scoresTextsPosY);
	newGO->AddComponent(score2Comp);

	// And add the bottom text explaining how to return to the start menu
	font = dae::ResourceManager::GetInstance().LoadFont("Minecraft.ttf", 16);
	auto* goBackComp = new dae::TextComponent("Press ESC or START to go back to the main menu", font);
	goBackComp->SetPosition(goBackPosX, goBackPosY);
	newGO->AddComponent(goBackComp);

	return newGO;
}


std::shared_ptr<dae::GameObject> MakeDeathScreenVersusVisuals()
{
	const auto titleAPosX = 170.f;
	const auto titleAPosY = 70.f;
	const auto titleBPosX = 250.f;
	const auto titleBPosY = 135.f;
	const auto scoreTextPosX = 150.f;
	const auto scoreTextPosY = 240.f;
	const auto goBackPosX = 126.f;
	const auto goBackPosY = 400.f;

	auto newGO = std::make_shared<dae::GameObject>();

	// Add the title
	auto font = dae::ResourceManager::GetInstance().LoadFont("Minecraft.ttf", 60);
	auto* titleAComp = new dae::TextComponent("PLAYER 2", font);
	titleAComp->SetPosition(titleAPosX, titleAPosY);
	newGO->AddComponent(titleAComp);
	auto* titleBComp = new dae::TextComponent("WON", font);
	titleBComp->SetPosition(titleBPosX, titleBPosY);
	newGO->AddComponent(titleBComp);

	// Add the score text (the "PLAYER 1 SCORE:", not the actual number)
	font = dae::ResourceManager::GetInstance().LoadFont("Minecraft.ttf", 38);
	auto* scoreComp = new dae::TextComponent("PLAYER 1 SCORE", font);
	scoreComp->SetPosition(scoreTextPosX, scoreTextPosY);
	newGO->AddComponent(scoreComp);

	// And add the bottom text explaining how to return to the start menu
	font = dae::ResourceManager::GetInstance().LoadFont("Minecraft.ttf", 16);
	auto* goBackComp = new dae::TextComponent("Press ESC or START to go back to the main menu", font);
	goBackComp->SetPosition(goBackPosX, goBackPosY);
	newGO->AddComponent(goBackComp);

	return newGO;
}


std::shared_ptr<dae::GameObject> MakeOneQbertVictoryDeathScreenLogic(int startScreenSceneIdx, QBert* qBertComp)
{
	const auto scorePosX = 255.f;
	const auto scorePosY = 290.f;

	auto victoryDeathScreenGO = std::make_shared<dae::GameObject>();

	victoryDeathScreenGO->AddComponent(new VictoryDeathScreen(startScreenSceneIdx));
	
	const auto font = dae::ResourceManager::GetInstance().LoadFont("Minecraft.ttf", 38);
	auto* scoreComp = new dae::TextComponent("000000", font);
	scoreComp->SetPosition(scorePosX, scorePosY);
	victoryDeathScreenGO->AddComponent(scoreComp);

	victoryDeathScreenGO->AddComponent(new MenuScoreDisplay(qBertComp, scoreComp));

	return victoryDeathScreenGO;
}


std::shared_ptr<dae::GameObject> MakeTwoQbertsVictoryDeathScreenLogic(int startScreenSceneIdx, std::vector<QBert*>* qBertCompVector)
{
	const auto scorePosY = 290.f;
	const auto scoreP1PosX = 125.f;
	const auto scoreP2PosX = 385.f;

	auto victoryDeathScreenGO = std::make_shared<dae::GameObject>();

	victoryDeathScreenGO->AddComponent(new VictoryDeathScreen(startScreenSceneIdx));


	// Make the score for P1
	const auto font = dae::ResourceManager::GetInstance().LoadFont("Minecraft.ttf", 38);
	auto* scoreComp1 = new dae::TextComponent("000000", font);
	scoreComp1->SetPosition(scoreP1PosX, scorePosY);
	victoryDeathScreenGO->AddComponent(scoreComp1);
	victoryDeathScreenGO->AddComponent(new MenuScoreDisplay(qBertCompVector->operator[](0), scoreComp1));

	// And then one for P2
	auto* scoreComp2 = new dae::TextComponent("000000", font);
	scoreComp2->SetPosition(scoreP2PosX, scorePosY);
	victoryDeathScreenGO->AddComponent(scoreComp2);
	victoryDeathScreenGO->AddComponent(new MenuScoreDisplay(qBertCompVector->operator[](1), scoreComp2));

	return victoryDeathScreenGO;
}