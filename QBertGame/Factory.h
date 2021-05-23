#pragma once
#include <memory>

const int g_NrRows = 7;
const float g_CubesActualWidth = 64.f;
const float g_CubesActualHeight = 64.f;
const int g_EnemiesLeftSpawnPosX = 284;
const float g_EnemiesRightSpawnPosX = 349;
const float g_EnemiesSpawnPosY = 110;

namespace dae
{
	class GameObject;
}

std::shared_ptr<dae::GameObject> MakeQBert();

std::shared_ptr<dae::GameObject> MakeSlickSam(bool isSlick, bool isLeft, float  moveInterval);

std::shared_ptr<dae::GameObject> MakeUggWrongway(bool isUgg, bool isLeft, float  moveInterval);

