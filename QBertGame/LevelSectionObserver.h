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
	explicit LevelSectionObserver(const std::shared_ptr<dae::GameObject>& gameObject, dae::QBert* qBertComp, Pyramid* pyramid);
	explicit LevelSectionObserver(const std::shared_ptr<dae::GameObject>& gameObject, dae::QBert* qBertComp, Pyramid* pyramid, std::vector<SlickSam*>* slickSamCompVector);
	~LevelSectionObserver() override;

	void SetQBert(dae::QBert* qBertComp);
	void SetPyramid(Pyramid* pyramid);
	void SetSlickSamVector(std::vector<SlickSam*>* slickSamCompVector);

	void Initialize() override;
	void Update(const float) override {}
	void OnNotify(const dae::Event& event) override;

	bool CheckAllCubesTurned() const;
	void WinSection();

private:
	dae::QBert* m_QBertComp{};
	Pyramid* m_Pyramid;
	std::vector<SlickSam*>* m_SlickSamCompVector{};
	std::shared_ptr<dae::GameObject> m_GameObject{};
	bool m_SectionComplete;
};

