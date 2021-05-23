#pragma once
#include <memory>
#include "Observer.h"
#include "BaseComponent.h"


class UggWrongway;
class SlickSam;
class Pyramid;

namespace dae
{
	class GraphicsComponent;
	class QBert;
}

class LevelSectionObserver final : public dae::BaseComponent, public dae::Observer
{
public:
	explicit LevelSectionObserver(const std::shared_ptr<dae::GameObject>& gameObject, dae::QBert* qBertComp, Pyramid* pyramid,
		bool spawnSlickSams, bool spawnUggWrongs,
		float slickSamSpawnInterval = 0, float slickSamMoveInterval = 0,
		float uggWrongSpawnInterval = 0, float uggWrongMoveInterval = 0);
	~LevelSectionObserver() override;

	void SetQBert(dae::QBert* qBertComp);
	void SetPyramid(Pyramid* pyramid);

	void Initialize() override;
	void Update(const float deltaTime) override;
	void OnNotify(const dae::Event& event) override;

	bool CheckAllCubesTurned() const;
	void WinSection();
	void ClearEverything();
	bool CheckCollidingUggWrong() const;
	void KillCollidingSlickSam() const;
	void KillFallenSlickSam() const;
	void KillFallenUggWrong() const;

	void AddSlickSam(bool isSlick, bool isLeft);
	void AddUggWrongway(bool isUgg, bool isLeft);

private:
	std::shared_ptr<dae::GameObject> m_GameObject{};
	dae::QBert* m_QBertComp{};
	Pyramid* m_Pyramid;
	
	const bool m_SpawnSlickSams;
	std::vector<SlickSam*>* m_SlickSamCompVector;
	float m_SlickSamSpawnTimer, m_SlickSamSpawnInterval, m_SlickSamMoveInterval;

	const bool m_SpawnUggWrongs;
	std::vector<UggWrongway*>* m_UggWrongCompVector;
	float m_UggWrongSpawnTimer1, m_UggWrongSpawnTimer2, m_UggWrongSpawnInterval, m_UggWrongMoveInterval;

	bool m_SectionComplete;
};

