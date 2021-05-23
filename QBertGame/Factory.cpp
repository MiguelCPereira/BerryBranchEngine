#include "Factory.h"
#include "GameObject.h"
#include "GraphicsComponent.h"
#include "SceneManager.h"
#include "SlickSam.h"
#include "Scene.h"
#include "QBert.h"
#include "UggWrongway.h"

std::shared_ptr<dae::GameObject> MakeQBert()
{
	const auto spriteWidth = 17.f;
	const auto spriteHeight = 16.f;
	const auto initialPosX = 308.f;
	const auto initialPosY = 50.f;
	const auto actualWidth = 49.f;
	const auto actualHeight = 48.f;

	auto qBertGO = std::make_shared<dae::GameObject>();
	qBertGO->AddComponent(new dae::QBert(qBertGO, g_NrRows, g_CubesActualWidth, g_CubesActualHeight, spriteWidth, spriteHeight));
	qBertGO->AddComponent(new dae::GraphicsComponent("QBert Spritesheet.png", initialPosX, initialPosY, actualWidth, actualHeight, spriteWidth * 2, 0, spriteWidth, spriteHeight));

	return qBertGO;
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

