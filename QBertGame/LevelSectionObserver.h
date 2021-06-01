#pragma once
#include <memory>
#include "Observer.h"
#include "BaseComponent.h"


class Disk;
class Coily;
class UggWrongway;
class SlickSam;
class Pyramid;
class QBert;

namespace dae
{
	class GraphicsComponent;
}

class LevelSectionObserver final : public dae::BaseComponent, public dae::Observer
{
public:
	explicit LevelSectionObserver(float transitionTime, std::vector<QBert*>* qBertCompVector, int gameMode); // An empty observer just for the level title scenes
	explicit LevelSectionObserver(const std::shared_ptr<dae::GameObject>& gameObject, std::vector<QBert*>* qBertCompVector, std::vector<dae::GraphicsComponent*>* qBertGraphicsVector,
		Pyramid* pyramid, std::vector<Disk*>* disksVector, int deathSceneIdx, int level, int gameMode, bool spawnSlickSams, bool spawnUggWrongs, float slickSamSpawnInterval = 0, float uggWrongSpawnInterval = 0);

	~LevelSectionObserver() override;

	void SetQBertVector(std::vector<QBert*>* qBertCompVector);
	void SetPyramid(Pyramid* pyramid);

	void Initialize() override;
	void Update(const float deltaTime) override;
	void OnNotify(const dae::Event& event) override;

	void DeadP1Update(const float deltaTime);
	void DeadP2Update(const float deltaTime);


	bool CheckAllCubesTurned() const;
	bool CheckCollidingCoily(int qBertIdx) const;
	bool CheckCollidingUggWrong(int qBertIdx) const;
	void DestroyUsedDisk() const;
	void KillCollidingSlickSam() const;
	void KillFallenSlickSam() const;
	void KillFallenUggWrong() const;
	void KillFallenCoily();
	void ClearAllEnemies();
	void ClearRemainingDisks() const;

	void WinSection();
	void LevelWonAnimation(const float deltaTime);
	void ChangeFreezeEverything(bool freeze) const;
	void ChangeSection(int newSectionIdx = 0) const;

	void AddCoily(bool isLeft);
	void AddSlickSam(bool isSlick, bool isLeft);
	void AddUggWrongway(bool isUgg, bool isLeft);

private:
	std::shared_ptr<dae::GameObject> m_GameObject{};
	Observer* m_ThisObserver{};
	std::vector<QBert*>* m_QBertCompVector;
	std::vector<dae::GraphicsComponent*>* m_QBertGraphicsVector;
	Pyramid* m_Pyramid;
	std::vector<Disk*>* m_DisksVector;
	const int m_DeathSceneIdx;

	bool m_QBertP1JustFell;
	bool m_QBertP1JustTookDisk;
	bool m_QBertP2JustFell;
	bool m_QBertP2JustTookDisk;

	Coily* m_CoilyComp;
	bool m_SpawnCoily;
	float m_CoilySpawnTimer, m_CoilySpawnDelay, m_CoilyMoveInterval;

	const bool m_SpawnSlickSams;
	std::vector<SlickSam*>* m_SlickSamCompVector;
	float m_SlickSamSpawnTimer, m_SlickSamSpawnInterval, m_SlickSamMoveInterval;

	const bool m_SpawnUggWrongs;
	std::vector<UggWrongway*>* m_UggWrongCompVector;
	float m_UggWrongSpawnTimer1, m_UggWrongSpawnTimer2, m_UggWrongSpawnInterval, m_UggWrongMoveInterval;

	bool m_SectionComplete;
	float m_AnimationTimer, m_FullAnimationTime;
	float m_FlashingTimer, m_FlashingColorTime;
	float m_ClearDisksTimer, m_ClearDisksPause;
	bool m_StartPostAnimationPause;
	float m_PostAnimationTimer, m_PostAnimationPause;
	int m_CurrentFlashingColor;
	bool m_EverythingClear;
	const int m_Level;

	bool m_DeadQbertP1, m_DeadQbertP2;
	float m_DeadQbertP1Timer, m_DeadQbertP2Timer, m_DeadQbertMaxTime;
	bool m_DeathEmptyScene;
	float m_DeathEmptySceneTimer, m_DeathEmptySceneMaxTime;

	float m_LevelTitleTimer, m_LevelTitleScreenTime;

	const int m_GameMode; // 1 is Solo, 2 is Coop, 3 is Versus
};

