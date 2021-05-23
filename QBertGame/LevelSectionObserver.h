#pragma once
#include <memory>
#include "Observer.h"
#include "BaseComponent.h"


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
		bool spawnSlickSams = false, float slickSamSpawnInterval = 0, float slickSamMoveInterval = 0);
	~LevelSectionObserver() override;

	void SetQBert(dae::QBert* qBertComp);
	void SetPyramid(Pyramid* pyramid);
	void SetSlickSamVector(std::vector<SlickSam*>* slickSamCompVector);

	void Initialize() override;
	void Update(const float deltaTime) override;
	void OnNotify(const dae::Event& event) override;

	bool CheckAllCubesTurned() const;
	void WinSection();

	void AddSlickSam(bool isSlick, bool isLeft);

private:
	dae::QBert* m_QBertComp{};
	Pyramid* m_Pyramid;
	std::shared_ptr<dae::GameObject> m_GameObject{};
	bool m_SectionComplete;
	const bool m_SpawnSlickSams;
	std::vector<SlickSam*>* m_SlickSamCompVector;
	float m_SlickSamSpawnTimer, m_SlickSamSpawnInterval, m_SlickSamMoveInterval;
	bool m_SlickSamVectorModified = false;
};

