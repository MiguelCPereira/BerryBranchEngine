#pragma once
#include <memory>
#include "Observer.h"
#include "BaseComponent.h"

class LevelSectionObserver;

class GameObserver : public dae::BaseComponent, public dae::Observer
{
public:
	explicit GameObserver(const std::shared_ptr<dae::GameObject>& gameObject, LevelSectionObserver* lvlSectionObserverComp, std::vector<std::shared_ptr<dae::GameObject>>* nextSectionObserverGOs);
	~GameObserver() override;

	void SetLvlSectionObserver(LevelSectionObserver* lvlSectionObserverComp);

	void Initialize() override;
	void Update(const float) override {}
	void OnNotify(const dae::Event& event) override;

	void WinLevel();
	void WinGame();

private:
	LevelSectionObserver* m_LvlSectionObserverComp;
	std::vector<std::shared_ptr<dae::GameObject>>* m_NextSectionObserverGOs{};
	std::shared_ptr<dae::GameObject> m_GameObject{};
	int m_CurrentSection; // This counter starts in 1 and loops back to 1 once a level is complete
	int m_CurrentSectionCounter; // While this counter starts in 1 also, but counts up to the size of the section GOs vector
};

