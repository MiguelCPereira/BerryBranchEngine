#include "GameObserver.h"

#include <iostream>
#include "GameObject.h"
#include "LevelSectionObserver.h"
#include "SceneManager.h"

GameObserver::GameObserver(const std::shared_ptr<dae::GameObject>& gameObject, LevelSectionObserver* lvlSectionObserverComp, std::vector<std::shared_ptr<dae::GameObject>>* nextSectionObserverGOs)
	: m_LvlSectionObserverComp(lvlSectionObserverComp)
	, m_NextSectionObserverGOs(nextSectionObserverGOs)
	, m_GameObject(gameObject)
	, m_CurrentSection(1)
	, m_CurrentSectionCounter(1)
{}

GameObserver::~GameObserver()
{
	if (m_LvlSectionObserverComp != nullptr)
		m_LvlSectionObserverComp->GetSubject()->RemoveObserver(this);
}

void GameObserver::Initialize()
{
	if (m_LvlSectionObserverComp != nullptr)
		m_LvlSectionObserverComp->GetSubject()->AddObserver(this);
}

void GameObserver::SetLvlSectionObserver(LevelSectionObserver* lvlSectionObserverComp)
{
	if (m_LvlSectionObserverComp != nullptr)
		m_LvlSectionObserverComp->GetSubject()->RemoveObserver(this);

	m_LvlSectionObserverComp = lvlSectionObserverComp;

	if (m_LvlSectionObserverComp != nullptr)
		m_LvlSectionObserverComp->GetSubject()->AddObserver(this);
}

void GameObserver::OnNotify(const dae::Event& event)
{
	switch (event)
	{
	case dae::Event::ColorChange:
		m_CurrentSection++;
		m_CurrentSectionCounter++;
		
		if(m_CurrentSection > 4)
		{
			m_CurrentSection = 1;
			WinLevel();
		}

		if (m_CurrentSectionCounter <= int(m_NextSectionObserverGOs->size()))
		{
			auto& scene = dae::SceneManager::GetInstance();
			scene.ChangeScene(scene.GetCurrentSceneIdx() + 1);
			SetLvlSectionObserver(m_NextSectionObserverGOs->operator[](m_CurrentSectionCounter)->GetComponent<LevelSectionObserver>());
		}
		else WinGame();
		
		break;
	}
}

void GameObserver::WinLevel()
{
	std::cout << "LEVEL COMPLETE\n";
}

void GameObserver::WinGame()
{
	std::cout << "GAME WON!!!\n";
}
