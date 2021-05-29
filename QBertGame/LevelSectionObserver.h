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
	explicit LevelSectionObserver(float transitionTime, QBert* qBertComp); // An empty observer just for the level title scenes
	explicit LevelSectionObserver(const std::shared_ptr<dae::GameObject>& gameObject, const std::shared_ptr<dae::GameObject>& qBertGO, Pyramid* pyramid,
		std::vector<Disk*>* disksVector, int level, bool spawnSlickSams, bool spawnUggWrongs, float slickSamSpawnInterval = 0, float uggWrongSpawnInterval = 0);

	~LevelSectionObserver() override;

	void SetQBert(QBert* qBertComp);
	void SetPyramid(Pyramid* pyramid);

	void Initialize() override;
	void Update(const float deltaTime) override;
	void OnNotify(const dae::Event& event) override;

	bool CheckAllCubesTurned() const;
	bool CheckCollidingCoily() const;
	bool CheckCollidingUggWrong() const;
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
	void ChangeSection() const;

	void AddCoily(bool isLeft);
	void AddSlickSam(bool isSlick, bool isLeft);
	void AddUggWrongway(bool isUgg, bool isLeft);

private:
	std::shared_ptr<dae::GameObject> m_GameObject{};
	Observer* m_ThisObserver{};
	QBert* m_QBertComp{};
	dae::GraphicsComponent* m_QBertGraphics{};
	Pyramid* m_Pyramid;
	std::vector<Disk*>* m_DisksVector;

	bool m_QBertJustFell;
	bool m_QBertJustTookDisk;
	
	Coily* m_CoilyComp{};
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

	bool m_DeadQbert;
	float m_DeadQbertTimer, m_DeadQbertMaxTime;
	bool m_DeathEmptyScene;
	float m_DeathEmptySceneTimer, m_DeathEmptySceneMaxTime;

	float m_LevelTitleTimer, m_LevelTitleScreenTime;
};

