#pragma once
#include <memory>
#include <vector>

class Disk;
const int g_NrRows = 7;
const float g_CubesActualWidth = 64.f;
const float g_CubesActualHeight = 64.f;
const int g_EnemiesLeftSpawnPosX = 284;
const float g_EnemiesRightSpawnPosX = 349;
const float g_EnemiesSpawnPosY = 110;
const float g_MapCenterX = 332.f;
const float g_DiskTopRowY = 40;
const auto g_InitialQbertPosY = 60.f;

class QBert;

namespace dae
{
	class GraphicsComponent;
	class GameObject;
}

std::vector<std::shared_ptr<dae::GameObject>> MakeQBert();

std::shared_ptr<dae::GameObject> MakeCoily(QBert* qBertComp, bool isLeft, float  moveInterval, bool controlledByPlayer);

std::shared_ptr<dae::GameObject> MakeSlickSam(bool isSlick, bool isLeft, float  moveInterval);

std::shared_ptr<dae::GameObject> MakeUggWrongway(bool isUgg, bool isLeft, float  moveInterval);

std::shared_ptr<dae::GameObject> MakeLevelTitle(int lvlNr, int gameMode); // 1 is Solo, 2 is Coop, 3 is Versus

std::shared_ptr<dae::GameObject> MakeLevelTransition(QBert* qBertComp);

std::shared_ptr<dae::GameObject> MakeFPSCounter();

std::shared_ptr<dae::GameObject> MakeHeartForDisplay(bool playerOne, float posY);

std::vector<std::shared_ptr<dae::GameObject>>* MakeLivesDisplayVisuals(bool playerOne, int livesAmount);

std::shared_ptr<dae::GameObject> MakeScoreDisplayVisuals(bool playerOne);

std::shared_ptr<dae::GameObject> MakeLevelDisplayVisuals(bool coOpOn);

std::shared_ptr<dae::GameObject> MakeRoundDisplayVisuals(bool coOpOn);

std::vector<std::shared_ptr<dae::GameObject>> MakeUI(std::vector<QBert*>* qBertCompVector, bool coOpOn);

std::shared_ptr<dae::GameObject> MakeDiskGO(int row, bool isLeft, int colorIdx);

std::vector<std::shared_ptr<dae::GameObject>>* MakeDiskGOsVector(int level, int colorIdx);

std::shared_ptr<dae::GameObject> MakeStartScreenVisuals();

std::shared_ptr<dae::GameObject> MakeStartScreenLogic(int soloModeSceneIdx, int coopModeSceneIdx, int versusModeSceneIdx);

std::shared_ptr<dae::GameObject> MakeVictoryScreenSoloVisuals();

std::shared_ptr<dae::GameObject> MakeVictoryScreenVersusVisuals();

std::shared_ptr<dae::GameObject> MakeDeathScreenSoloVisuals();

std::shared_ptr<dae::GameObject> MakeDeathScreenVersusVisuals();

std::shared_ptr<dae::GameObject> MakeVictoryDeathScreenLogic(int startScreenSceneIdx, QBert* qBertComp);
