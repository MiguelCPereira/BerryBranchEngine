#include "LevelSectionObserver.h"
#include <iostream>
#include "Cube.h"
#include "QBert.h"
#include "GameObject.h"
#include "GraphicsComponent.h"
#include "Pyramid.h"
#include "Scene.h"
#include "SceneManager.h"
#include "SlickSam.h"
#include "Factory.h"
#include "UggWrongway.h"
#include "Coily.h"

LevelSectionObserver::LevelSectionObserver(float transitionTime, QBert* qBertComp)
	: m_GameObject()
	, m_QBertComp(qBertComp)
	, m_Pyramid()

	, m_QBertJustFell()

	, m_SpawnCoily()
	, m_CoilySpawnTimer()
	, m_CoilySpawnDelay()
	, m_CoilyMoveInterval()

	, m_SpawnSlickSams()
	, m_SlickSamSpawnTimer()
	, m_SlickSamSpawnInterval()
	, m_SlickSamMoveInterval()

	, m_SpawnUggWrongs()
	, m_UggWrongSpawnTimer1()
	, m_UggWrongSpawnTimer2()
	, m_UggWrongSpawnInterval()
	, m_UggWrongMoveInterval()

	, m_SectionComplete()
	, m_AnimationTimer()
	, m_FullAnimationTime()
	, m_FlashingTimer()
	, m_FlashingColorTime()
	, m_PostAnimationTimer()
	, m_PostAnimationPause()
	, m_CurrentFlashingColor()
	, m_EverythingClear()
	, m_Level()

	, m_DeadQbert()
	, m_DeadQbertTimer()
	, m_DeadQbertMaxTime()
	, m_DeathEmptyScene()
	, m_DeathEmptySceneTimer()
	, m_DeathEmptySceneMaxTime()

	, m_LevelTitleTimer(0.f)
	, m_LevelTitleScreenTime(transitionTime)
{
}



LevelSectionObserver::LevelSectionObserver(const std::shared_ptr<dae::GameObject>& gameObject, QBert* qBertComp, Pyramid* pyramid,
	int level, bool spawnSlickSams, bool spawnUggWrongs, float slickSamSpawnInterval, float uggWrongSpawnInterval)
	: m_GameObject(gameObject)
	, m_QBertComp(qBertComp)
	, m_Pyramid(pyramid)

	, m_QBertJustFell(false)

	, m_SpawnCoily(true)
	, m_CoilySpawnTimer(5.f) // We start at 5 so the first Coily only takes 3 sec to spawn
	, m_CoilySpawnDelay(8.f)
	, m_CoilyMoveInterval(1.f)

	, m_SpawnSlickSams(spawnSlickSams)
	, m_SlickSamSpawnTimer(0.f)
	, m_SlickSamSpawnInterval(slickSamSpawnInterval)
	, m_SlickSamMoveInterval(1.f)

	, m_SpawnUggWrongs(spawnUggWrongs)
	, m_UggWrongSpawnTimer1(0.f)
	, m_UggWrongSpawnTimer2(0.f)
	, m_UggWrongSpawnInterval(uggWrongSpawnInterval)
	, m_UggWrongMoveInterval(1.f)

	, m_SectionComplete(false)
	, m_AnimationTimer(0.f)
	, m_FullAnimationTime(2.f)
	, m_FlashingTimer(0.1f)
	, m_FlashingColorTime(0.1f)
	, m_PostAnimationTimer(0.f)
	, m_PostAnimationPause(1.f)
	, m_CurrentFlashingColor(3)
	, m_EverythingClear(false)
	, m_Level(level)

	, m_DeadQbert(false)
	, m_DeadQbertTimer(0.f)
	, m_DeadQbertMaxTime(2.f)
	, m_DeathEmptyScene(false)
	, m_DeathEmptySceneTimer(0.f)
	, m_DeathEmptySceneMaxTime(1.f)

	, m_LevelTitleTimer()
	, m_LevelTitleScreenTime()
{
	// So it only takes 2 secs for the first Ugg/Wrongway to spawn
	if (m_UggWrongSpawnInterval - 2.f > 0.f)
	{
		m_UggWrongSpawnTimer1 = m_UggWrongSpawnInterval - 2.f;
		m_UggWrongSpawnTimer2 = m_UggWrongSpawnInterval - 2.f;
	}
	
	m_SlickSamCompVector = new std::vector<SlickSam*>;
	m_UggWrongCompVector = new std::vector<UggWrongway*>;
}


LevelSectionObserver::~LevelSectionObserver()
{
	if (m_QBertComp != nullptr)
		m_QBertComp->GetSubject()->RemoveObserver(this);

	if (m_CoilyComp != nullptr)
		m_CoilyComp->GetSubject()->RemoveObserver(this);

	if (m_SlickSamCompVector->empty() == false)
	{
		for (size_t i = 0; i < m_SlickSamCompVector->size(); i++)
		{
			if (m_SlickSamCompVector->operator[](i) != nullptr)
				m_SlickSamCompVector->operator[](i)->GetSubject()->RemoveObserver(this);
		}
	}

	if (m_UggWrongCompVector->empty() == false)
	{
		for (size_t i = 0; i < m_UggWrongCompVector->size(); i++)
		{
			if (m_UggWrongCompVector->operator[](i) != nullptr)
				m_UggWrongCompVector->operator[](i)->GetSubject()->RemoveObserver(this);
		}
	}

	delete m_Pyramid;
	m_Pyramid = nullptr;
}

void LevelSectionObserver::Initialize()
{
	m_ThisObserver = this;
	if (m_QBertComp != nullptr)
	{
		m_QBertComp->GetSubject()->AddObserver(this);
		m_QBertComp->SetFrozen(false);
	}
}

void LevelSectionObserver::SetQBert(QBert* qBertComp)
{
	if (m_QBertComp != nullptr)
		m_QBertComp->GetSubject()->RemoveObserver(this);

	m_QBertComp = qBertComp;

	if (m_QBertComp != nullptr)
		m_QBertComp->GetSubject()->AddObserver(this);
}

void LevelSectionObserver::SetPyramid(Pyramid* pyramid)
{
	delete m_Pyramid;
	m_Pyramid = nullptr;
	m_Pyramid = pyramid;
}

void LevelSectionObserver::AddCoily(bool isLeft)
{
	auto newCoilyGO = MakeCoily(isLeft, m_CoilyMoveInterval);
	dae::SceneManager::GetInstance().GetCurrentScene()->Add(newCoilyGO);
	auto* newCoilyComp = newCoilyGO->GetComponent<Coily>();

	if (newCoilyComp != nullptr)
	{
		newCoilyComp->GetSubject()->AddObserver(this);
		m_CoilyComp = newCoilyComp;
	}
	else
	{
		std::cout << "Coily creation failed\n";
	}
}

void LevelSectionObserver::AddSlickSam(bool isSlick, bool isLeft)
{
	auto newSlickSamGO = MakeSlickSam(isSlick, isLeft, m_SlickSamMoveInterval);
	dae::SceneManager::GetInstance().GetCurrentScene()->Add(newSlickSamGO);
	auto* newSlickSamComp = newSlickSamGO->GetComponent<SlickSam>();

	if (newSlickSamComp != nullptr)
	{
		newSlickSamComp->GetSubject()->AddObserver(this);
		m_SlickSamCompVector->push_back(newSlickSamComp);
	}
	else
	{
		std::cout << "Slick/Sam creation failed\n";
	}
}

void LevelSectionObserver::AddUggWrongway(bool isUgg, bool isLeft)
{
	auto newUggWrongGO = MakeUggWrongway(isUgg, isLeft, m_UggWrongMoveInterval);
	dae::SceneManager::GetInstance().GetCurrentScene()->Add(newUggWrongGO);
	auto* newUggWrongComp = newUggWrongGO->GetComponent<UggWrongway>();

	if (newUggWrongComp != nullptr)
	{
		newUggWrongComp->GetSubject()->AddObserver(this);
		m_UggWrongCompVector->push_back(newUggWrongComp);
	}
	else
	{
		std::cout << "Ugg/Wrongway creation failed\n";
	}
}

void LevelSectionObserver::OnNotify(const dae::Event& event)
{
	bool cubeTurned;

	// This if statement will only not run if the instance of this class was created with
	// the first constructor - which means it's only gonna be used for a level transition
	if (m_LevelTitleScreenTime == 0.f)
	{
		switch (event)
		{

		case dae::Event::QBertLanded:
			// 1 is subtracted from the idx, because the cubes are numbered from 1 to 28
			// But they're stored counting from 0 in the vector
			cubeTurned = m_Pyramid->m_CubeGOVector[m_QBertComp->GetPositionIndex() - 1]->GetComponent<Cube>()->TurnCube();

			if (cubeTurned)
				m_QBertComp->ScoreIncrease(25);

			if (CheckAllCubesTurned())
				WinSection();

			KillCollidingSlickSam();

			if (m_DeadQbert == false)
			{
				if (CheckCollidingUggWrong() || CheckCollidingCoily())
				{
					ChangeFreezeEverything(true);
					m_DeadQbert = true;
					m_QBertComp->Die();

					// Make QBert curse
					m_QBertComp->SetCursesHidden(false);
				}
			}
			break;

			
		case dae::Event::QBertFell:
			if (m_QBertJustFell == false)
			{
				ChangeFreezeEverything(true);
				m_DeadQbert = true;
				m_QBertComp->Die();
				m_QBertJustFell = true;

				// Make QBert curse
				m_QBertComp->SetCursesHidden(false);
				break;
			}

			
		case dae::Event::SlickSamLanded:
			for (size_t i = 0; i < m_SlickSamCompVector->size(); i++)
				m_Pyramid->m_CubeGOVector[m_SlickSamCompVector->operator[](i)->GetPositionIndex() - 1]->GetComponent<Cube>()->SlickSamTurnCube();

			KillCollidingSlickSam();
			break;


		case dae::Event::SlickSamFell:
			KillFallenSlickSam();
			break;


		case dae::Event::UggWrongwayLanded:
			if (m_DeadQbert == false)
			{
				if (CheckCollidingUggWrong())
				{
					ChangeFreezeEverything(true);
					m_DeadQbert = true;
					m_QBertComp->Die();

					// Make QBert curse
					m_QBertComp->SetCursesHidden(false);
				}
			}
			break;


		case dae::Event::UggWrongwayFell:
			KillFallenUggWrong();
			break;

		case dae::Event::CoilyLanded:
			if (m_DeadQbert == false)
			{
				if (CheckCollidingCoily())
				{
					ChangeFreezeEverything(true);
					m_DeadQbert = true;
					m_QBertComp->Die();

					// Make QBert curse
					m_QBertComp->SetCursesHidden(false);
				}
			}
			break;
			
		case dae::Event::CoilyFell:
			KillFallenCoily();
			break;
		}
	}
}

bool LevelSectionObserver::CheckAllCubesTurned() const
{
	for(const std::shared_ptr<dae::GameObject>& cube : m_Pyramid->m_CubeGOVector)
	{
		if (cube->GetComponent<Cube>()->GetIsTurned() == false)
			return false;
	}
	
	return true;
}

bool LevelSectionObserver::CheckCollidingCoily() const
{
	if (m_QBertComp->GetAirborne() == false && m_CoilyComp != nullptr)
	{
		if (m_QBertComp->GetPositionIndex() == m_CoilyComp->GetPositionIndex())
		{
			return true;
		}
	}

	return false;
}

bool LevelSectionObserver::CheckCollidingUggWrong() const
{
	if (m_QBertComp->GetAirborne() == false)
	{
		for (size_t i = 0; i < m_UggWrongCompVector->size(); i++)
		{
			auto* uggWrong = m_UggWrongCompVector->operator[](i);
			if (uggWrong->GetStartedLeft())
			{
				if (m_QBertComp->GetPositionIndex() == uggWrong->GetPositionIndex() + uggWrong->GetCurrentRow() &&
					uggWrong->GetAirborne() == false)
				{
					return true;
				}
			}
			else
			{
				if (m_QBertComp->GetPositionIndex() == uggWrong->GetPositionIndex() + uggWrong->GetCurrentRow() + 1 &&
					uggWrong->GetAirborne() == false)
				{
					return true;
				}
			}
		}
		return false;
	}

	return false;
}

void LevelSectionObserver::KillCollidingSlickSam() const
{
	if (m_QBertComp->GetAirborne() == false)
	{
		auto nrSlickSams = m_SlickSamCompVector->size();
		for (size_t i = 0; i < nrSlickSams; i++)
		{
			
			if (m_QBertComp->GetPositionIndex() == m_SlickSamCompVector->operator[](i)->GetPositionIndex() &&
				m_SlickSamCompVector->operator[](i)->GetAirborne() == false)
			{
				auto* deadSlickSam = m_SlickSamCompVector->operator[](i);
				m_SlickSamCompVector->erase(std::find(m_SlickSamCompVector->begin(), m_SlickSamCompVector->end(), deadSlickSam));
				deadSlickSam->Die();
				i--;
				nrSlickSams--;
				m_QBertComp->ScoreIncrease(300);
			}
		}
	}
}

void LevelSectionObserver::KillFallenSlickSam() const
{
	auto nrSlickSams = int(m_SlickSamCompVector->size());
	for (auto i = 0; i < nrSlickSams; i++)
	{
		auto* slickSam = m_SlickSamCompVector->operator[](i);
		if (slickSam->GetIsAlive() == false)
		{
			m_SlickSamCompVector->erase(std::find(m_SlickSamCompVector->begin(), m_SlickSamCompVector->end(), slickSam));
			slickSam->Die();
			i--;
			nrSlickSams--;
		}
	}
}

void LevelSectionObserver::KillFallenUggWrong() const
{
	auto nrUggWrongs = int(m_UggWrongCompVector->size());
	for (auto i = 0; i < nrUggWrongs; i++)
	{
		auto* uggWrong = m_UggWrongCompVector->operator[](i);
		if (uggWrong->GetIsAlive() == false)
		{
			m_UggWrongCompVector->erase(std::find(m_UggWrongCompVector->begin(), m_UggWrongCompVector->end(), uggWrong));
			uggWrong->Die();
			i--;
			nrUggWrongs--;
		}
	}
}

void LevelSectionObserver::KillFallenCoily()
{
	auto* deadCoily = m_CoilyComp;
	m_CoilyComp = nullptr;
	deadCoily->Die();
	m_SpawnCoily = true;
	m_QBertComp->ScoreIncrease(500);
}

void LevelSectionObserver::ClearAllEnemies()
{
	if(m_CoilyComp != nullptr)
	{
		auto* coily = m_CoilyComp;
		m_CoilyComp = nullptr;
		coily->Die();
	}
	
	auto nrComponents = int(m_SlickSamCompVector->size());
	for (auto i = 0; i < nrComponents; i++)
	{
		auto* slickSam = m_SlickSamCompVector->operator[](0);
		m_SlickSamCompVector->erase(m_SlickSamCompVector->begin());
		slickSam->Die();
	}

	m_SlickSamSpawnTimer = 0.f;


	nrComponents = int(m_UggWrongCompVector->size());
	for (auto i = 0; i < nrComponents; i++)
	{
		auto* uggWrong = m_UggWrongCompVector->operator[](0);
		m_UggWrongCompVector->erase(m_UggWrongCompVector->begin());
		uggWrong->Die();
	}

	m_UggWrongSpawnTimer1 = 0.f;
	m_UggWrongSpawnTimer2 = -2.f;
}

void LevelSectionObserver::WinSection()
{
	if (m_SectionComplete == false)
	{
		ChangeFreezeEverything(true);
		m_SectionComplete = true;
	}
}

void LevelSectionObserver::ChangeFreezeEverything(bool freeze) const
{
	m_QBertComp->SetFrozen(freeze);

	if (m_CoilyComp != nullptr)
		m_CoilyComp->SetFrozen(freeze);
	
	for (size_t i = 0; i < m_SlickSamCompVector->size(); i++)
		m_SlickSamCompVector->operator[](i)->SetFrozen(freeze);

	for (size_t i = 0; i < m_UggWrongCompVector->size(); i++)
		m_UggWrongCompVector->operator[](i)->SetFrozen(freeze);
	
}

void LevelSectionObserver::ChangeSection()
{
	if (m_QBertComp != nullptr)
	{
		// This if statement will only run if the instance of this class was created with
		// the first constructor - which means it's only gonna be used for a level transition
		if (m_LevelTitleScreenTime > 0.f)
		{
			m_QBertComp->SetRound(1);
			m_QBertComp->SetLevel(m_QBertComp->GetLevel() + 1);
		}
		else
		{
			m_QBertComp->ResetPosition();
			m_QBertComp->SetFrozen(true);
			m_QBertComp->SetRound(m_QBertComp->GetRound() + 1);




			// Delete everything from this observer, as it will still be active after
			// The round transition, as QBert is stored as a global
			
			if (m_QBertComp != nullptr)
				m_QBertComp->GetSubject()->RemoveObserver(m_ThisObserver);

			if (m_CoilyComp != nullptr)
				m_CoilyComp->GetSubject()->RemoveObserver(m_ThisObserver);

			if (m_SlickSamCompVector->empty() == false)
			{
				for (size_t i = 0; i < m_SlickSamCompVector->size(); i++)
				{
					if (m_SlickSamCompVector->operator[](i) != nullptr)
						m_SlickSamCompVector->operator[](i)->GetSubject()->RemoveObserver(m_ThisObserver);
				}
			}

			if (m_UggWrongCompVector->empty() == false)
			{
				for (size_t i = 0; i < m_UggWrongCompVector->size(); i++)
				{
					if (m_UggWrongCompVector->operator[](i) != nullptr)
						m_UggWrongCompVector->operator[](i)->GetSubject()->RemoveObserver(m_ThisObserver);
				}
			}

			delete m_Pyramid;
			m_Pyramid = nullptr;
		}
	}
	
	auto& scene = dae::SceneManager::GetInstance();
	scene.ChangeScene(scene.GetCurrentSceneIdx() + 1);
}

void LevelSectionObserver::Update(const float deltaTime)
{
	// This first if statement will only not run if the instance of this class was created with
	// the first constructor - which means it's only gonna be used for a level transition
	if (m_LevelTitleScreenTime <= 0.f)
	{
		if (m_SectionComplete == false)
		{
			if(m_DeadQbert)
			{
				m_DeadQbertTimer += deltaTime;
				if (m_DeadQbertTimer >= m_DeadQbertMaxTime)
				{
					m_QBertComp->RevertToLastPosition();
					m_QBertComp->SetHideGraphics(true);
					m_QBertComp->SetCursesHidden(true);
					ClearAllEnemies();
					m_DeadQbertTimer = 0.f;
					m_DeadQbert = false;
					m_DeathEmptyScene = true;
				}
			}
			else
			{
				if(m_DeathEmptyScene)
				{
					m_DeathEmptySceneTimer += deltaTime;
					if(m_DeathEmptySceneTimer >= m_DeathEmptySceneMaxTime)
					{
						if (m_QBertJustFell)
							m_QBertJustFell = false;

						m_QBertComp->SetHideGraphics(false);
						m_QBertComp->SetFrozen(false);
						m_DeathEmptySceneTimer = 0.f;
						m_DeathEmptyScene = false;
					}
				}
				else
				{
					if (m_SpawnCoily)
					{
						m_CoilySpawnTimer += deltaTime;
						
						if (m_CoilySpawnTimer >= m_CoilySpawnDelay)
						{
							// A random 50/50 chance of spawning either a left or right
							bool isLeft = false;
							if ((rand() % 2) + 1 == 1)
								isLeft = true;

							m_CoilySpawnTimer = 0.f;
							m_SpawnCoily = false;
							AddCoily(isLeft);
						}
					}
					
					
					if (m_SpawnSlickSams)
					{
						m_SlickSamSpawnTimer += deltaTime;

						if (m_SlickSamSpawnTimer >= m_SlickSamSpawnInterval)
						{
							bool isSlick = false;
							bool isLeft = false;

							// A random 50/50 chance of spawning either a Slick or a Sam
							if ((rand() % 2) + 1 == 1)
								isSlick = true;

							// A random 50/50 chance of spawning either a left or right
							if ((rand() % 2) + 1 == 1)
								isLeft = true;

							AddSlickSam(isSlick, isLeft);
							m_SlickSamSpawnTimer -= m_SlickSamSpawnInterval;
						}
					}

					if (m_SpawnUggWrongs)
					{
						m_UggWrongSpawnTimer1 += deltaTime;
						m_UggWrongSpawnTimer2 += deltaTime;

						if (m_UggWrongSpawnTimer1 >= m_UggWrongSpawnInterval)
						{
							bool isUgg = false;

							if ((rand() % 2) + 1 == 1)
								isUgg = true;

							AddUggWrongway(isUgg, true);
							m_UggWrongSpawnTimer1 -= m_UggWrongSpawnInterval;
						}

						// An extra second is added so the right spawner has a tiny delay compared to the left one
						if (m_UggWrongSpawnTimer2 >= m_UggWrongSpawnInterval + 2.f)
						{
							bool isUgg = false;

							if ((rand() % 2) + 1 == 1)
								isUgg = true;

							AddUggWrongway(isUgg, false);
							m_UggWrongSpawnTimer2 -= m_UggWrongSpawnInterval;
						}
					}
				}
			}
		}
		else
		{
			LevelWonAnimation(deltaTime);
		}
	}
	else
	{
		m_LevelTitleTimer += deltaTime;
		
		if (m_LevelTitleTimer >= m_LevelTitleScreenTime)
			ChangeSection();
	}
}

void LevelSectionObserver::LevelWonAnimation(const float deltaTime)
{
	m_AnimationTimer += deltaTime;
	m_FlashingTimer += deltaTime;

	if (m_AnimationTimer < m_FullAnimationTime)
	{
		// If it's time to change color
		if (m_FlashingTimer >= m_FlashingColorTime)
		{
			if (m_CurrentFlashingColor == 1)
			{
				// Turn every cube into the 2nd row color (yellow, blue, dark grey, grey-yellow, no-base blue or dark blue)
				for (const std::shared_ptr<dae::GameObject>& cube : m_Pyramid->m_CubeGOVector)
					cube->GetComponent<Cube>()->MakeCube2ndColor();

				m_CurrentFlashingColor = 2;
			}
			else if (m_CurrentFlashingColor == 2)
			{
				// Turn every cube into the 3rd row color (red, green, blue, purple, pink or dark purple)
				for (const std::shared_ptr<dae::GameObject>& cube : m_Pyramid->m_CubeGOVector)
					cube->GetComponent<Cube>()->MakeCube3rdColor();

				m_CurrentFlashingColor = 3;
			}
			else
			{
				// Turn every cube into the 1st row color (blue, yellow, white, light-blue, no-base yellow or baby-blue)
				for (const std::shared_ptr<dae::GameObject>& cube : m_Pyramid->m_CubeGOVector)
					cube->GetComponent<Cube>()->MakeCube1stColor();

				m_CurrentFlashingColor = 1;
			}

			m_FlashingTimer = 0.f;
		}
	}
	else // Animation complete
	{
		if (m_EverythingClear == false)
		{
			m_EverythingClear = true;
			ClearAllEnemies();
			m_QBertComp->SetHideGraphics(true);

			// Set cubes to original turned color
			for (const std::shared_ptr<dae::GameObject>& cube : m_Pyramid->m_CubeGOVector)
			{
				if(m_Level == 2)
					cube->GetComponent<Cube>()->MakeCube3rdColor();
				else
					cube->GetComponent<Cube>()->MakeCube2ndColor();
			}
		}
		
		m_PostAnimationTimer += deltaTime;
		if (m_PostAnimationTimer >= m_PostAnimationPause)
		{
			m_QBertComp->SetFrozen(false);
			ChangeSection();
		}
	}
}
