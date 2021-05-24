#include "Factory.h"
#include "GameObject.h"
#include "GraphicsComponent.h"
#include "LevelSectionObserver.h"
#include "SceneManager.h"
#include "SlickSam.h"
#include "QBert.h"
#include "UggWrongway.h"

std::vector<std::shared_ptr<dae::GameObject>> MakeQBert()
{
	auto actualWidth = 55.f;
	auto actualHeight = 29.f;
	const auto spriteWidth = 17.f;
	const auto spriteHeight = 16.f;
	const auto initialPosX = 308.f;
	const auto initialPosY = 50.f;

	auto cursesGO = std::make_shared<dae::GameObject>();
	cursesGO->AddComponent(new dae::GraphicsComponent("QBert Curses.png", -20, -20, actualWidth, actualHeight));

	actualWidth = 49.f;
	actualHeight = 48.f;
	
	auto qBertGO = std::make_shared<dae::GameObject>();
	qBertGO->AddComponent(new dae::QBert(qBertGO, cursesGO, g_NrRows, g_CubesActualWidth, g_CubesActualHeight, spriteWidth, spriteHeight));
	qBertGO->AddComponent(new dae::GraphicsComponent("QBert Spritesheet.png", initialPosX, initialPosY, actualWidth, actualHeight, spriteWidth * 2, 0, spriteWidth, spriteHeight));

	std::vector< std::shared_ptr<dae::GameObject>> returnVector;
	returnVector.push_back(std::move(qBertGO));
	returnVector.push_back(std::move(cursesGO));
	
	return returnVector;
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
			newGO->AddComponent(new SlickSam(newGO, g_NrRows, g_CubesActualWidth, g_CubesActualHeight, spriteWidth, spriteHeight, 2, moveInterval, true));
			newGO->AddComponent(new dae::GraphicsComponent("Slick Sam Spritesheet.png", g_EnemiesLeftSpawnPosX, g_EnemiesSpawnPosY, actualWidth, actualHeight, 0, 0, spriteWidth, spriteHeight));
		}
		else
		{
			newGO->AddComponent(new SlickSam(newGO, g_NrRows, g_CubesActualWidth, g_CubesActualHeight, spriteWidth, spriteHeight, 3, moveInterval, true));
			newGO->AddComponent(new dae::GraphicsComponent("Slick Sam Spritesheet.png", g_EnemiesRightSpawnPosX, g_EnemiesSpawnPosY, actualWidth, actualHeight, 0, 0, spriteWidth, spriteHeight));
		}
	}
	else
	{
		if (isLeft)
		{
			newGO->AddComponent(new SlickSam(newGO, g_NrRows, g_CubesActualWidth, g_CubesActualHeight, spriteWidth, spriteHeight, 2, moveInterval, false));
			newGO->AddComponent(new dae::GraphicsComponent("Slick Sam Spritesheet.png", g_EnemiesLeftSpawnPosX, g_EnemiesSpawnPosY, actualWidth, actualHeight, spriteWidth, spriteHeight, spriteWidth, spriteHeight));
		}
		else
		{
			newGO->AddComponent(new SlickSam(newGO, g_NrRows, g_CubesActualWidth, g_CubesActualHeight, spriteWidth, spriteHeight, 3, moveInterval, false));
			newGO->AddComponent(new dae::GraphicsComponent("Slick Sam Spritesheet.png", g_EnemiesRightSpawnPosX, g_EnemiesSpawnPosY, actualWidth, actualHeight, spriteWidth, spriteHeight, spriteWidth, spriteHeight));
		}
	}

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
			newGO->AddComponent(new UggWrongway(newGO, g_NrRows, g_CubesActualWidth, g_CubesActualHeight, spriteWidth, spriteHeight, 22, moveInterval, true, true));
			newGO->AddComponent(new dae::GraphicsComponent("Ugg Wrongway Spritesheet.png", leftSpawnPositionX, spawnPositionY, actualWidth, actualHeight, spriteWidth, 0, spriteWidth, spriteHeight));
		}
		else
		{
			newGO->AddComponent(new UggWrongway(newGO, g_NrRows, g_CubesActualWidth, g_CubesActualHeight, spriteWidth, spriteHeight, 28, moveInterval, true, false));
			newGO->AddComponent(new dae::GraphicsComponent("Ugg Wrongway Spritesheet.png", rightSpawnPositionX, spawnPositionY, actualWidth, actualHeight, spriteWidth*3, 0, spriteWidth, spriteHeight));
		}
	}
	else
	{
		if (isLeft)
		{
			newGO->AddComponent(new UggWrongway(newGO, g_NrRows, g_CubesActualWidth, g_CubesActualHeight, spriteWidth, spriteHeight, 22, moveInterval, false, true));
			newGO->AddComponent(new dae::GraphicsComponent("Ugg Wrongway Spritesheet.png", leftSpawnPositionX, spawnPositionY, actualWidth, actualHeight, spriteWidth, spriteHeight, spriteWidth, spriteHeight));
		}
		else
		{
			newGO->AddComponent(new UggWrongway(newGO, g_NrRows, g_CubesActualWidth, g_CubesActualHeight, spriteWidth, spriteHeight, 28, moveInterval, false, false));
			newGO->AddComponent(new dae::GraphicsComponent("Ugg Wrongway Spritesheet.png", rightSpawnPositionX, spawnPositionY, actualWidth, actualHeight, spriteWidth*3, spriteHeight, spriteWidth, spriteHeight));
		}
	}

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


std::shared_ptr<dae::GameObject> MakeLevelTransition()
{
	const float transitionTime = 2.f;

	auto sectionObserverGO = std::make_shared<dae::GameObject>();
	sectionObserverGO->AddComponent(new LevelSectionObserver(transitionTime));

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
