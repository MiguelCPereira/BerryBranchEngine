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
#include "Disk.h"
#include "P2CoilyInput.h"
#include "SoundServiceLocator.h"
#include "SoundSystem.h"

LevelSectionObserver::LevelSectionObserver(float transitionTime, std::vector<QBert*>* qBertCompVector, int gameMode)
	: m_GameObject()
	, m_QBertCompVector(qBertCompVector)
	, m_QBertGraphicsVector()
	, m_Pyramid()
	, m_DeathSceneIdx()
	, m_PauseScreenGraphics()

	, m_QBertP1JustFell()
	, m_QBertP1JustTookDisk()
	, m_QBertP2JustFell()
	, m_QBertP2JustTookDisk()

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

	, m_AnimationTimer()
	, m_FullAnimationTime()
	, m_FlashingTimer()
	, m_FlashingColorTime()
	, m_ClearDisksTimer()
	, m_ClearDisksPause()
	, m_PostAnimationTimer()
	, m_PostAnimationPause()
	, m_CurrentFlashingColor()
	, m_EverythingClear()
	, m_Level()
	, m_ColorIdx()

	, m_DeadQbertP1()
	, m_DeadQbertP2()
	, m_DeadQbertP1Timer()
	, m_DeadQbertP2Timer()
	, m_DeadQbertMaxTime()
	, m_DeathEmptySceneTimer()
	, m_DeathEmptySceneMaxTime()

	, m_LevelTitleTimer(0.f)
	, m_LevelTitleScreenTime(transitionTime)

	, m_GameMode(gameMode)
	, m_CoopP1SpawnPosX()
	, m_CoopP2SpawnPosX()
	, m_CoopSpawnPosY()

	, m_CurrentState(LevelSectionState::ST_InterLevelAnimation)
	, m_StateBeforePause()
{
}


LevelSectionObserver::LevelSectionObserver(const std::shared_ptr<dae::GameObject>& gameObject, std::vector<QBert*>* qBertCompVector,
	std::vector<dae::GraphicsComponent*>* qBertGraphicsVector, Pyramid* pyramid, int deathSceneIdx, dae::GraphicsComponent* pauseScreenGraphics,
	int level, int gameMode, int colorIdx, float coopP1SpawnPosX, float coopP2SpawnPosX, float coopSpawnPosY,
	bool spawnSlickSams, bool spawnUggWrongs, float slickSamSpawnInterval, float uggWrongSpawnInterval)
	: m_GameObject(gameObject)
	, m_QBertCompVector(qBertCompVector)
	, m_QBertGraphicsVector(qBertGraphicsVector)
	, m_Pyramid(pyramid)
	, m_DisksVector()
	, m_DeathSceneIdx(deathSceneIdx)
	, m_PauseScreenGraphics(pauseScreenGraphics)

	, m_QBertP1JustFell(false)
	, m_QBertP1JustTookDisk(false)
	, m_QBertP2JustFell(false)
	, m_QBertP2JustTookDisk(false)

	, m_CoilyComp()
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

	, m_AnimationTimer(0.f)
	, m_FullAnimationTime(2.f)
	, m_FlashingTimer(0.1f)
	, m_FlashingColorTime(0.1f)
	, m_ClearDisksTimer(0.f)
	, m_ClearDisksPause(1.f)
	, m_PostAnimationTimer(0.f)
	, m_PostAnimationPause(1.f)
	, m_CurrentFlashingColor(3)
	, m_EverythingClear(false)
	, m_Level(level)
	, m_ColorIdx(colorIdx)

	, m_DeadQbertP1(false)
	, m_DeadQbertP2(false)
	, m_DeadQbertP1Timer(0.f)
	, m_DeadQbertP2Timer(0.f)
	, m_DeadQbertMaxTime(2.f)
	, m_DeathEmptySceneTimer(0.f)
	, m_DeathEmptySceneMaxTime(1.f)

	, m_LevelTitleTimer()
	, m_LevelTitleScreenTime()

	, m_GameMode(gameMode)
	, m_CoopP1SpawnPosX(coopP1SpawnPosX)
	, m_CoopP2SpawnPosX(coopP2SpawnPosX)
	, m_CoopSpawnPosY(coopSpawnPosY)

	, m_CurrentState(LevelSectionState::ST_NormalSpawning)
	, m_StateBeforePause()
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
	if (m_QBertCompVector->empty() == false)
	{
		for (size_t i = 0; i < m_QBertCompVector->size(); i++)
		{
			if (m_QBertCompVector->operator[](i) != nullptr)
				m_QBertCompVector->operator[](i)->GetSubject()->RemoveObserver(this);
		}
	}

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

	if (m_DisksVector->empty() == false)
	{
		for (size_t i = 0; i < m_DisksVector->size(); i++)
		{
			if (m_DisksVector->operator[](i) != nullptr)
			{
				m_DisksVector->operator[](i)->GetSubject()->RemoveObserver(this);
			}
		}
	}
}

void LevelSectionObserver::Initialize()
{
	// Initialize also resets every value that might be changed during gameplay,
	// in case the scene is loaded again (aka, the round needs to restart)


	m_ThisObserver = this;

	if (m_QBertCompVector->empty() == false)
	{
		for (size_t i = 0; i < m_QBertCompVector->size(); i++)
		{
			if (m_QBertCompVector->operator[](i) != nullptr)
			{
				m_QBertCompVector->operator[](i)->GetSubject()->AddObserver(this);
				m_QBertCompVector->operator[](i)->SetFrozen(false);
			}
		}
	}

	// This statement will only run if the instance of this class was created with
	// the first constructor - which means it's only gonna be used for a level transition
	if (m_CurrentState == LevelSectionState::ST_InterLevelAnimation)
	{
		m_LevelTitleTimer = 0.f;
		SoundServiceLocator::GetSoundSystem().Play("../Data/Sounds/Level Screen Tune.wav", 0.1f);
	}
	else
	{
		// All the modifiable variable should be re-set to their default values, in case the scene has been played before
		m_QBertP1JustFell = false;
		m_SpawnCoily = true;
		m_CoilySpawnTimer = 5.f;
		m_SlickSamSpawnTimer = 0.f;
		m_UggWrongSpawnTimer1 = 0.f;
		m_UggWrongSpawnTimer2 = 0.f;
		m_AnimationTimer = 0.f;
		m_FlashingTimer = 0.1f;
		m_ClearDisksTimer = 0.f;
		m_PostAnimationTimer = 0.f;
		m_CurrentFlashingColor = 3;
		m_EverythingClear = false;
		m_DeadQbertP1 = false;
		m_DeadQbertP2 = false;
		m_DeadQbertP1Timer = 0.f;
		m_DeadQbertP2Timer = 0.f;
		m_DeathEmptySceneTimer = 0.f;
		m_CurrentState = LevelSectionState::ST_NormalSpawning;

		
		// If in Co-op Mode, the positions of the QBerts must be changed to the bottom corners of the pyramid
		if (m_QBertCompVector->empty() == false && m_GameMode == 2)
		{
			m_QBertCompVector->operator[](0)->SetNewPositionIndexes(22, 7);
			m_QBertGraphicsVector->operator[](0)->SetPosition(m_CoopP1SpawnPosX, m_CoopSpawnPosY);
			m_QBertCompVector->operator[](1)->SetNewPositionIndexes(28, 7);
			m_QBertGraphicsVector->operator[](1)->SetPosition(m_CoopP2SpawnPosX, m_CoopSpawnPosY);
			m_QBertCompVector->operator[](0)->BackToGround();
			m_QBertCompVector->operator[](0)->SetFrozen(false);
			m_QBertCompVector->operator[](1)->BackToGround();
			m_QBertCompVector->operator[](1)->SetFrozen(false);
		}

		
		// If the scene is being loaded for the first time, we need to initialize the disk vector
		if (m_DisksVector == nullptr)
			m_DisksVector = new std::vector<Disk*>;

		// Then we fill this vector with the adequate amount of disks and add them to the scene
		auto* diskGOsVector = MakeDiskGOsVector(m_Level, m_ColorIdx);
		for (size_t i = 0; i < diskGOsVector->size(); i++)
		{
			m_DisksVector->push_back(diskGOsVector->operator[](i)->GetComponent<Disk>());
			dae::SceneManager::GetInstance().GetCurrentScene()->Add(diskGOsVector->operator[](i));
		}

		// And we start observing said disks
		if (m_DisksVector->empty() == false)
		{
			for (size_t i = 0; i < m_DisksVector->size(); i++)
			{
				auto* disk = m_DisksVector->operator[](i);

				if (disk != nullptr)
				{
					disk->GetSubject()->AddObserver(this);
				}
			}
		}

		
		// And finally, all the pyramid cubes should be reset, in case the scene has been played before
		if (m_Pyramid != nullptr)
		{
			for (auto cube : m_Pyramid->m_CubeGOVector)
				cube->GetComponent<Cube>()->ResetCube();
		}
	}
}

void LevelSectionObserver::SetQBertVector(std::vector<QBert*>* qBertCompVector)
{
	if (m_QBertCompVector->empty() == false)
	{
		for (size_t i = 0; i < m_QBertCompVector->size(); i++)
		{
			if (m_QBertCompVector->operator[](i) != nullptr)
				m_QBertCompVector->operator[](i)->GetSubject()->RemoveObserver(this);
		}
	}

	m_QBertCompVector = qBertCompVector;

	if (m_QBertCompVector->empty() == false)
	{
		for (size_t i = 0; i < m_QBertCompVector->size(); i++)
		{
			if (m_QBertCompVector->operator[](i) != nullptr)
				m_QBertCompVector->operator[](i)->GetSubject()->AddObserver(this);
		}
	}
}

void LevelSectionObserver::SetPyramid(Pyramid* pyramid)
{
	delete m_Pyramid;
	m_Pyramid = nullptr;
	m_Pyramid = pyramid;
}

void LevelSectionObserver::AddCoily(bool isLeft)
{
	auto newCoilyGO = MakeCoily(m_QBertCompVector, isLeft, m_CoilyMoveInterval, m_GameMode);
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

	if (m_GameMode == 3)
	{
		auto coilyPlayerInputGO = std::make_shared<dae::GameObject>();
		coilyPlayerInputGO->AddComponent(new P2CoilyInput(newCoilyGO));
		dae::SceneManager::GetInstance().GetCurrentScene()->Add(coilyPlayerInputGO);
		coilyPlayerInputGO->GetComponent<P2CoilyInput>()->Initialize();
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
	if (m_CurrentState != LevelSectionState::ST_InterLevelAnimation)
	{
		switch (event)
		{
		case dae::Event::PausePressed:
			if(m_CurrentState != LevelSectionState::ST_GamePaused)
			{
				m_StateBeforePause = m_CurrentState;
				m_CurrentState = LevelSectionState::ST_GamePaused;
				m_PauseScreenGraphics->SetPosition(0, 0);
				ChangeFreezeEverything(true);
			}
			else
			{
				m_CurrentState = m_StateBeforePause;
				m_PauseScreenGraphics->SetPosition(-2000, -2000);
				ChangeFreezeEverything(false);
			}
			break;

		case dae::Event::BackToMenu:
			if (m_CurrentState == LevelSectionState::ST_GamePaused)
			{
				m_CurrentState = LevelSectionState::ST_NormalSpawning;
				m_PauseScreenGraphics->SetPosition(-2000, -2000);
				ChangeFreezeEverything(false);
				ClearAllEnemies();
				ChangeSection(0);
			}
			break;


		case dae::Event::QBertLandedP1:
			// If P2 died before P1 lands, the landing should have no consequences, as well as if the round was won before
			if (m_DeadQbertP2 == false && m_CurrentState == LevelSectionState::ST_NormalSpawning)
			{
				// 1 is subtracted from the idx, because the cubes are numbered from 1 to 28
				// But they're stored counting from 0 in the vector
				cubeTurned = m_Pyramid->m_CubeGOVector[m_QBertCompVector->operator[](0)->GetPositionIndex() - 1]->GetComponent<Cube>()->TurnCube();

				if (cubeTurned)
					m_QBertCompVector->operator[](0)->ScoreIncrease(25);

				if (CheckAllCubesTurned())
					WinSection();

				KillCollidingSlickSam();

				if (m_DeadQbertP1 == false && m_DeadQbertP2 == false) // So once one dies, the other can't die until the map has been clean
				{
					if (CheckCollidingUggWrong(0) || CheckCollidingCoily(0))
					{
						SoundServiceLocator::GetSoundSystem().Play("../Data/Sounds/QBert Hit.wav", 0.07f);
						ChangeFreezeEverything(true);
						m_DeadQbertP1 = true;

						m_QBertCompVector->operator[](0)->Die();

						// Make QBert curse
						SoundServiceLocator::GetSoundSystem().Play("../Data/Sounds/Swearing.wav", 0.1f);
						m_QBertCompVector->operator[](0)->SetCursesHidden(false);
					}
				}
			}
			break;


		case dae::Event::QBertLandedP2:
			// If P1 died before P2 lands, the landing should have no consequences, as well as if the round was won before
			if (m_DeadQbertP1 == false && m_CurrentState == LevelSectionState::ST_NormalSpawning)
			{
				// 1 is subtracted from the idx, because the cubes are numbered from 1 to 28
				// But they're stored counting from 0 in the vector
				cubeTurned = m_Pyramid->m_CubeGOVector[m_QBertCompVector->operator[](1)->GetPositionIndex() - 1]->GetComponent<Cube>()->TurnCube();

				if (cubeTurned)
					m_QBertCompVector->operator[](1)->ScoreIncrease(25);

				if (CheckAllCubesTurned())
					WinSection();

				KillCollidingSlickSam();

				if (m_DeadQbertP1 == false && m_DeadQbertP2 == false) // So once one dies, the other can't die until the map has been clean
				{
					if (CheckCollidingUggWrong(1) || CheckCollidingCoily(1))
					{
						SoundServiceLocator::GetSoundSystem().Play("../Data/Sounds/QBert Hit.wav", 0.07f);
						ChangeFreezeEverything(true);
						m_DeadQbertP2 = true;

						m_QBertCompVector->operator[](1)->Die();

						// Make QBert curse
						SoundServiceLocator::GetSoundSystem().Play("../Data/Sounds/Swearing.wav", 0.1f);
						m_QBertCompVector->operator[](1)->SetCursesHidden(false);
					}
				}
			}
			break;


		case dae::Event::DiskFlightEndedP1:
			DestroyUsedDisk();
			m_QBertCompVector->operator[](0)->BackToGround();
			m_QBertCompVector->operator[](0)->SetNewPositionIndexes(1, 1);
			m_QBertCompVector->operator[](0)->SetFrozen(false);

			// If P2 died before P1 lands, the landing should have no consequences, as well as if the round was won before
			if (m_DeadQbertP2 == false && m_CurrentState == LevelSectionState::ST_NormalSpawning)
			{
				cubeTurned = m_Pyramid->m_CubeGOVector[m_QBertCompVector->operator[](0)->GetPositionIndex() - 1]->GetComponent<Cube>()->TurnCube();

				if (cubeTurned)
					m_QBertCompVector->operator[](0)->ScoreIncrease(25);

				if (CheckAllCubesTurned())
					WinSection();
			}

			break;


		case dae::Event::DiskFlightEndedP2:
			DestroyUsedDisk();
			m_QBertCompVector->operator[](1)->BackToGround();
			m_QBertCompVector->operator[](1)->SetNewPositionIndexes(1, 1);
			m_QBertCompVector->operator[](1)->SetFrozen(false);

			// If P1 died before P2 lands, the landing should have no consequences, as well as if the round was won before
			if (m_DeadQbertP1 == false && m_CurrentState == LevelSectionState::ST_NormalSpawning)
			{
				cubeTurned = m_Pyramid->m_CubeGOVector[m_QBertCompVector->operator[](1)->GetPositionIndex() - 1]->GetComponent<Cube>()->TurnCube();

				if (cubeTurned)
					m_QBertCompVector->operator[](1)->ScoreIncrease(25);

				if (CheckAllCubesTurned())
					WinSection();
			}

			break;


		case dae::Event::QBertFellP1:
			// If P2 died before P1 falls, the fall should have no consequences, as well as if the round was won before
			if (m_DeadQbertP1 == false && m_DeadQbertP2 == false && m_CurrentState == LevelSectionState::ST_NormalSpawning)
			{
				m_QBertP1JustTookDisk = false;
				for (size_t i = 0; i < m_DisksVector->size(); i++)
				{
					auto* disk = m_DisksVector->operator[](i);
					if (disk->GetHasBeenUsed() == false && disk->GetActivated() == false && disk->GetRow() == m_QBertCompVector->operator[](0)->GetCurrentRow())
					{
						if (disk->GetIsLeft() && m_QBertCompVector->operator[](0)->GetLastJumpedOffLeft() && m_QBertCompVector->operator[](0)->GetLastJumpedOffDown() == false)
						{
							m_QBertP1JustTookDisk = true;
							disk->Activate(m_QBertCompVector->operator[](0), m_QBertGraphicsVector->operator[](0), true);
							break;
						}
						if (disk->GetIsLeft() == false && m_QBertCompVector->operator[](0)->GetLastJumpedOffLeft() == false && m_QBertCompVector->operator[](0)->GetLastJumpedOffDown() == false)
						{
							m_QBertP1JustTookDisk = true;
							disk->Activate(m_QBertCompVector->operator[](0), m_QBertGraphicsVector->operator[](0), true);
							break;
						}
					}
				}

				if (m_QBertP1JustFell == false && m_QBertP1JustTookDisk == false)
				{
					SoundServiceLocator::GetSoundSystem().Play("../Data/Sounds/QBert Fall.wav", 0.5f);
					ChangeFreezeEverything(true);
					m_DeadQbertP1 = true;

					m_QBertCompVector->operator[](0)->Die();

					m_QBertP1JustFell = true;

					// Make QBert curse
					SoundServiceLocator::GetSoundSystem().Play("../Data/Sounds/Swearing.wav", 0.1f);
					m_QBertCompVector->operator[](0)->SetCursesHidden(false);
					break;
				}
			}
			else
			{
				// P1 fell, but after P2 already died (so P1 jumped a tiny bit before P2 got hit / fell too)
				// In this case, P1 should receive no punishment, but they still need to re-spawn in their last position
				// So the "justfell" bool must still be changed
				m_QBertP1JustFell = true;
			}
			break;


		case dae::Event::QBertFellP2:
			// If P1 died before P2 falls, the fall should have no consequences, as well as if the round was won before
			if (m_DeadQbertP1 == false && m_DeadQbertP2 == false && m_CurrentState == LevelSectionState::ST_NormalSpawning)
			{
				m_QBertP2JustTookDisk = false;
				for (size_t i = 0; i < m_DisksVector->size(); i++)
				{
					auto* disk = m_DisksVector->operator[](i);
					if (disk->GetHasBeenUsed() == false && disk->GetActivated() == false && disk->GetRow() == m_QBertCompVector->operator[](1)->GetCurrentRow())
					{
						if (disk->GetIsLeft() && m_QBertCompVector->operator[](1)->GetLastJumpedOffLeft() && m_QBertCompVector->operator[](1)->GetLastJumpedOffDown() == false)
						{
							m_QBertP2JustTookDisk = true;
							disk->Activate(m_QBertCompVector->operator[](1), m_QBertGraphicsVector->operator[](1), false);
							break;
						}
						if (disk->GetIsLeft() == false && m_QBertCompVector->operator[](1)->GetLastJumpedOffLeft() == false && m_QBertCompVector->operator[](1)->GetLastJumpedOffDown() == false)
						{
							m_QBertP2JustTookDisk = true;
							disk->Activate(m_QBertCompVector->operator[](1), m_QBertGraphicsVector->operator[](1), false);
							break;
						}
					}
				}

				if (m_QBertP2JustFell == false && m_QBertP2JustTookDisk == false)
				{
					SoundServiceLocator::GetSoundSystem().Play("../Data/Sounds/QBert Fall.wav", 0.5f);
					ChangeFreezeEverything(true);
					m_DeadQbertP2 = true;

					m_QBertCompVector->operator[](1)->Die();

					m_QBertP2JustFell = true;

					// Make QBert curse
					SoundServiceLocator::GetSoundSystem().Play("../Data/Sounds/Swearing.wav", 0.1f);
					m_QBertCompVector->operator[](1)->SetCursesHidden(false);
					break;
				}
			}
			else
			{
				// P2 fell, but after P1 already died (so P2 jumped a tiny bit before P1 got hit / fell too)
				// In this case, P2 should receive no punishment, but they still need to re-spawn in their last position
				// So the "justfell" bool must still be changed
				m_QBertP2JustFell = true;
			}
			break;


		case dae::Event::SlickSamLanded:
			for (size_t i = 0; i < m_SlickSamCompVector->size(); i++)
				m_Pyramid->m_CubeGOVector[m_SlickSamCompVector->operator[](i)->GetPositionIndex() - 1]->GetComponent<Cube>()->SlickSamTurnCube();

			KillCollidingSlickSam();
			break;


		case dae::Event::SlickSamFell:
			KillFallenSlickSam();
			break;


		case dae::Event::UggWrongwayLanded:
			if (m_DeadQbertP1 == false && m_DeadQbertP2 == false) // So once one dies, the other can't die until the map has been clean
			{
				// Check P1
				if (CheckCollidingUggWrong(0))
				{
					SoundServiceLocator::GetSoundSystem().Play("../Data/Sounds/QBert Hit.wav", 0.07f);
					ChangeFreezeEverything(true);
					m_DeadQbertP1 = true;

					m_QBertCompVector->operator[](0)->Die();

					// Make QBert curse
					SoundServiceLocator::GetSoundSystem().Play("../Data/Sounds/Swearing.wav", 0.1f);
					m_QBertCompVector->operator[](0)->SetCursesHidden(false);

					break;
				}

				// Check P2
				if (m_GameMode == 2)
				{
					if (CheckCollidingUggWrong(1))
					{
						SoundServiceLocator::GetSoundSystem().Play("../Data/Sounds/QBert Hit.wav", 0.07f);
						ChangeFreezeEverything(true);
						m_DeadQbertP2 = true;

						m_QBertCompVector->operator[](1)->Die();

						// Make QBert curse
						SoundServiceLocator::GetSoundSystem().Play("../Data/Sounds/Swearing.wav", 0.1f);
						m_QBertCompVector->operator[](1)->SetCursesHidden(false);
					}
				}
			}
			break;


		case dae::Event::UggWrongwayFell:
			KillFallenUggWrong();
			break;

		case dae::Event::CoilyLanded:
			if (m_DeadQbertP1 == false && m_DeadQbertP2 == false) // So once one dies, the other can't die until the map has been clean
			{
				// Check For P1
				if (CheckCollidingCoily(0))
				{
					SoundServiceLocator::GetSoundSystem().Play("../Data/Sounds/QBert Hit.wav", 0.07f);
					ChangeFreezeEverything(true);
					m_DeadQbertP1 = true;

					m_QBertCompVector->operator[](0)->Die();

					// Make QBert curse
					SoundServiceLocator::GetSoundSystem().Play("../Data/Sounds/Swearing.wav", 0.1f);
					m_QBertCompVector->operator[](0)->SetCursesHidden(false);

					break;
				}

				// Check For P2
				if (m_GameMode == 2)
				{
					if (CheckCollidingCoily(1))
					{
						SoundServiceLocator::GetSoundSystem().Play("../Data/Sounds/QBert Hit.wav", 0.07f);
						ChangeFreezeEverything(true);
						m_DeadQbertP2 = true;

						m_QBertCompVector->operator[](1)->Die();

						// Make QBert curse
						SoundServiceLocator::GetSoundSystem().Play("../Data/Sounds/Swearing.wav", 0.1f);
						m_QBertCompVector->operator[](1)->SetCursesHidden(false);
					}
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
	for (const std::shared_ptr<dae::GameObject>& cube : m_Pyramid->m_CubeGOVector)
	{
		if (cube->GetComponent<Cube>()->GetIsTurned() == false)
			return false;
	}

	return true;
}

bool LevelSectionObserver::CheckCollidingCoily(int qBertIdx) const
{
	if (m_QBertCompVector->operator[](qBertIdx)->GetAirborne() == false && m_CoilyComp != nullptr)
	{
		if (m_QBertCompVector->operator[](qBertIdx)->GetPositionIndex() == m_CoilyComp->GetPositionIndex() && m_CoilyComp->GetAirborne() == false)
		{
			// This function only needs to be called in Versus Mode, as what it actually does is just notifying P2CoilyInput
			// to reset the Coily controllers and delete its components (and the deletion of said components, in the other 2 modes
			// is done by this class)
			if(m_GameMode == 3)
				m_CoilyComp->QBertHit();
			
			return true;
		}
	}

	return false;
}

bool LevelSectionObserver::CheckCollidingUggWrong(int qBertIdx) const
{
	if (m_QBertCompVector->operator[](qBertIdx)->GetAirborne() == false)
	{
		for (size_t i = 0; i < m_UggWrongCompVector->size(); i++)
		{
			auto* uggWrong = m_UggWrongCompVector->operator[](i);
			if (uggWrong->GetAirborne() == false)
			{
				if (uggWrong->GetStartedLeft())
				{
					if (m_QBertCompVector->operator[](qBertIdx)->GetPositionIndex() == uggWrong->GetPositionIndex() + uggWrong->GetCurrentRow())
						return true;
				}
				else
				{
					if (m_QBertCompVector->operator[](qBertIdx)->GetPositionIndex() == uggWrong->GetPositionIndex() + uggWrong->GetCurrentRow() + 1)
						return true;
				}
			}
		}
		return false;
	}

	return false;
}

void LevelSectionObserver::DestroyUsedDisk() const
{
	for (size_t i = 0; i < m_DisksVector->size(); i++)
	{
		auto* disk = m_DisksVector->operator[](i);
		if (disk->GetHasBeenUsed())
		{
			disk->SetHide(true);
			break;
		}
	}
}

void LevelSectionObserver::KillCollidingSlickSam() const
{
	if (m_GameMode != 2)
	{
		if (m_QBertCompVector->operator[](0)->GetAirborne() == false)
		{
			auto nrSlickSams = m_SlickSamCompVector->size();
			for (size_t j = 0; j < nrSlickSams; j++)
			{
				if (m_QBertCompVector->operator[](0)->GetPositionIndex() == m_SlickSamCompVector->operator[](j)->GetPositionIndex() &&
					m_SlickSamCompVector->operator[](j)->GetAirborne() == false)
				{
					auto* deadSlickSam = m_SlickSamCompVector->operator[](j);
					m_SlickSamCompVector->erase(std::find(m_SlickSamCompVector->begin(), m_SlickSamCompVector->end(), deadSlickSam));
					deadSlickSam->Die();
					j--;
					nrSlickSams--;
					m_QBertCompVector->operator[](0)->ScoreIncrease(300);
					SoundServiceLocator::GetSoundSystem().Play("../Data/Sounds/SlickSam Caught.wav", 0.3f);
				}
			}
		}
	}
	else
	{
		for (auto i = 0; i < int(m_QBertCompVector->size()); i++)
		{
			if (m_QBertCompVector->operator[](i)->GetAirborne() == false)
			{
				auto nrSlickSams = m_SlickSamCompVector->size();
				for (size_t j = 0; j < nrSlickSams; j++)
				{
					if (m_QBertCompVector->operator[](i)->GetPositionIndex() == m_SlickSamCompVector->operator[](j)->GetPositionIndex() &&
						m_SlickSamCompVector->operator[](j)->GetAirborne() == false)
					{
						auto* deadSlickSam = m_SlickSamCompVector->operator[](j);
						m_SlickSamCompVector->erase(std::find(m_SlickSamCompVector->begin(), m_SlickSamCompVector->end(), deadSlickSam));
						deadSlickSam->Die();
						j--;
						nrSlickSams--;
						m_QBertCompVector->operator[](i)->ScoreIncrease(300);
						SoundServiceLocator::GetSoundSystem().Play("../Data/Sounds/SlickSam Caught.wav", 0.3f);
					}
				}
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
	// If in Solo Mode, calling Coily's Die() function is P2CoilyInput's responsibility
	if (m_GameMode != 3)
	{
		auto* deadCoily = m_CoilyComp;
		m_CoilyComp = nullptr;
		deadCoily->Die();
	}

	m_CoilyComp = nullptr;
	m_SpawnCoily = true;

	for (auto i = 0; i < int(m_QBertCompVector->size()); i++)
		m_QBertCompVector->operator[](i)->ScoreIncrease(500);
}

void LevelSectionObserver::ClearAllEnemies()
{
	if (m_CoilyComp != nullptr)
	{
		auto* coily = m_CoilyComp;
		m_CoilyComp = nullptr;
		coily->Die();
		m_SpawnCoily = true;
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

void LevelSectionObserver::ClearRemainingDisks(bool addPoints) const
{
	int nrActiveDisks = 0;
	
	auto nrComponents = int(m_DisksVector->size());
	for (auto i = 0; i < nrComponents; i++)
	{
		auto* disk = m_DisksVector->operator[](0);
		m_DisksVector->erase(m_DisksVector->begin());
		disk->Die();
		nrActiveDisks++;
	}
	
	/*for (size_t i = 0; i < m_DisksVector->size(); i++)
	{
		auto* disk = m_DisksVector->operator[](i);
		if (disk->GetHasBeenUsed() == false)
		{
			disk->SetHide(true);
			nrActiveDisks++;
		}
	}*/

	if (addPoints)
	{
		SoundServiceLocator::GetSoundSystem().Play("../Data/Sounds/Clear Disks.wav", 0.1f);
		for (auto i = 0; i < int(m_QBertCompVector->size()); i++)
			m_QBertCompVector->operator[](i)->ScoreIncrease(nrActiveDisks * 50);
	}
}

void LevelSectionObserver::WinSection()
{
	if (m_CurrentState != LevelSectionState::ST_RoundWon)
	{
		SoundServiceLocator::GetSoundSystem().Play("../Data/Sounds/Round Complete Tune.wav", 0.1f);
		ChangeFreezeEverything(true);
		m_CurrentState = LevelSectionState::ST_RoundWon;
	}
}

void LevelSectionObserver::ChangeFreezeEverything(bool freeze) const
{
	for (auto i = 0; i < int(m_QBertCompVector->size()); i++)
		m_QBertCompVector->operator[](i)->SetFrozen(freeze);

	if (m_CoilyComp != nullptr)
		m_CoilyComp->SetFrozen(freeze);

	for (size_t i = 0; i < m_SlickSamCompVector->size(); i++)
		m_SlickSamCompVector->operator[](i)->SetFrozen(freeze);

	for (size_t i = 0; i < m_UggWrongCompVector->size(); i++)
		m_UggWrongCompVector->operator[](i)->SetFrozen(freeze);

	for (size_t i = 0; i < m_DisksVector->size(); i++)
		m_DisksVector->operator[](i)->SetFrozen(freeze);

}

void LevelSectionObserver::ChangeSection(int newSectionIdx) const
{
	if (m_CurrentState != LevelSectionState::ST_InterLevelAnimation)
	{
		for (auto i = 0; i < int(m_QBertCompVector->size()); i++)
		{
			m_QBertCompVector->operator[](i)->ResetPosition();
			m_QBertCompVector->operator[](i)->SetFrozen(true);




		// Stop observing everything once the round ends

			if (m_QBertCompVector->operator[](i) != nullptr)
				m_QBertCompVector->operator[](i)->GetSubject()->RemoveObserver(m_ThisObserver);
		}

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

		if (m_DisksVector->empty() == false)
		{
			for (size_t i = 0; i < m_DisksVector->size(); i++)
			{
				if (m_DisksVector->operator[](i) != nullptr)
				{
					m_DisksVector->operator[](i)->GetSubject()->RemoveObserver(m_ThisObserver);
				}
			}

			ClearRemainingDisks();
		}
	}

	// If going back to the Main Menu, reset QBerts scores
	if(newSectionIdx == 0)
	{
		for (auto i = 0; i < int(m_QBertCompVector->size()); i++)
		{
			auto qBert = m_QBertCompVector->operator[](i);
			qBert->ResetGameVariables();
			qBert->AnimationStopped();
			qBert->ResetPosition();
			qBert->BackToGround();
			if(qBert->AreGraphicsHidden())
				qBert->SetHideGraphics(false);
			qBert->SetCursesHidden(true);
			ChangeFreezeEverything(false);
		}
	}
	
	auto& scene = dae::SceneManager::GetInstance();
	scene.ChangeScene(newSectionIdx);
}

void LevelSectionObserver::Update(const float deltaTime)
{
	switch (m_CurrentState)
	{
	case LevelSectionState::ST_InterLevelAnimation:
		m_LevelTitleTimer += deltaTime;

		if (m_LevelTitleTimer >= m_LevelTitleScreenTime)
			ChangeSection(dae::SceneManager::GetInstance().GetCurrentSceneIdx() + 1);
		break;

		
	case LevelSectionState::ST_GamePaused:
		// Stop updating everything until paused is pressed again
		break;

	case LevelSectionState::ST_RoundWon:
		if(RoundWonAnimation(deltaTime))
		{
			ClearRemainingDisks();
			m_CurrentState = LevelSectionState::ST_PauseBeforeNextRound;
		}
		break;


	case LevelSectionState::ST_PauseBeforeNextRound:
		m_PostAnimationTimer += deltaTime;
		if (m_PostAnimationTimer >= m_PostAnimationPause)
		{
			for (auto i = 0; i < int(m_QBertCompVector->size()); i++)
				m_QBertCompVector->operator[](i)->SetFrozen(false);

			ChangeSection(dae::SceneManager::GetInstance().GetCurrentSceneIdx() + 1);
		}
		break;


	case LevelSectionState::ST_PlayerDying:
		if (m_DeadQbertP1)
		{
			if (DeadP1Update(deltaTime)) // This will only return true once the dying animation is done
				m_CurrentState = LevelSectionState::ST_PostDeathEmptyScene;
		}

		if (m_DeadQbertP2)
		{
			if (DeadP2Update(deltaTime))  // This will only return true once the dying animation is done
				m_CurrentState = LevelSectionState::ST_PostDeathEmptyScene;
		}
		break;

		
	case LevelSectionState::ST_PostDeathEmptyScene:
		m_DeathEmptySceneTimer += deltaTime;
		if (m_DeathEmptySceneTimer >= m_DeathEmptySceneMaxTime)
		{
			if (m_QBertP1JustFell)
				m_QBertP1JustFell = false;

			if (m_QBertP2JustFell)
				m_QBertP2JustFell = false;

			for (auto i = 0; i < int(m_QBertCompVector->size()); i++)
			{
				m_QBertCompVector->operator[](i)->BackToGround();

				if (m_QBertCompVector->operator[](i)->AreGraphicsHidden())
					m_QBertCompVector->operator[](i)->SetHideGraphics(false);

				m_QBertCompVector->operator[](i)->SetFrozen(false);
			}

			ChangeFreezeEverything(false);

			m_DeathEmptySceneTimer = 0.f;
			m_CurrentState = LevelSectionState::ST_NormalSpawning;
		}
		break;

		
	case LevelSectionState::ST_NormalSpawning:
		if (m_DeadQbertP1 || m_DeadQbertP2)
		{
			m_CurrentState = LevelSectionState::ST_PlayerDying;
			break;
		}
		
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
			if (m_UggWrongSpawnTimer2 >= m_UggWrongSpawnInterval + 2.1f)
			{
				bool isUgg = false;

				if ((rand() % 2) + 1 == 1)
					isUgg = true;

				AddUggWrongway(isUgg, false);
				m_UggWrongSpawnTimer2 -= m_UggWrongSpawnInterval;
			}
		}
		break;
	}
}

bool LevelSectionObserver::DeadP1Update(const float deltaTime)
{
	m_DeadQbertP1Timer += deltaTime;
	if (m_DeadQbertP1Timer >= m_DeadQbertMaxTime)
	{
		if (m_QBertP1JustFell)
			m_QBertCompVector->operator[](0)->RevertToLastPosition();
		if (m_QBertP2JustFell)
			m_QBertCompVector->operator[](1)->RevertToLastPosition();

		if (m_QBertCompVector->operator[](0)->AreGraphicsHidden() == false)
		{
			m_QBertCompVector->operator[](0)->AnimationStopped();
			m_QBertCompVector->operator[](0)->SetHideGraphics(true);
		}
		if (m_QBertCompVector->operator[](1)->AreGraphicsHidden() == false)
		{
			m_QBertCompVector->operator[](1)->AnimationStopped();
			m_QBertCompVector->operator[](1)->SetHideGraphics(true);
		}
		
		m_QBertCompVector->operator[](0)->SetCursesHidden(true);
		ClearAllEnemies();

		if (m_QBertCompVector->operator[](0)->GetCurrentLives() <= 0)
		{
			if (m_QBertP1JustFell)
				m_QBertP1JustFell = false;

			m_QBertCompVector->operator[](0)->BackToGround();
			m_QBertCompVector->operator[](0)->SetFrozen(false);
			m_QBertCompVector->operator[](0)->SetCursesHidden(true);
			m_QBertCompVector->operator[](1)->BackToGround();
			m_QBertCompVector->operator[](1)->SetFrozen(false);
			m_QBertCompVector->operator[](1)->SetCursesHidden(true);

			ChangeSection(m_DeathSceneIdx);
			return false;
		}
		else
		{
			m_DeadQbertP1Timer = 0.f;
			m_DeadQbertP1 = false;
			return true;
		}
	}

	return false;;
}

bool LevelSectionObserver::DeadP2Update(const float deltaTime)
{
	m_DeadQbertP2Timer += deltaTime;
	if (m_DeadQbertP2Timer >= m_DeadQbertMaxTime)
	{
		if (m_QBertP1JustFell)
			m_QBertCompVector->operator[](0)->RevertToLastPosition();
		if (m_QBertP2JustFell)
			m_QBertCompVector->operator[](1)->RevertToLastPosition();

		if (m_QBertCompVector->operator[](0)->AreGraphicsHidden() == false)
		{
			m_QBertCompVector->operator[](0)->AnimationStopped();
			m_QBertCompVector->operator[](0)->SetHideGraphics(true);
		}
		
		if (m_QBertCompVector->operator[](1)->AreGraphicsHidden() == false)
		{
			m_QBertCompVector->operator[](1)->AnimationStopped();
			m_QBertCompVector->operator[](1)->SetHideGraphics(true);
		}
		
		m_QBertCompVector->operator[](1)->SetCursesHidden(true);
		ClearAllEnemies();

		if (m_QBertCompVector->operator[](1)->GetCurrentLives() <= 0)
		{
			if (m_QBertP2JustFell)
				m_QBertP2JustFell = false;

			m_QBertCompVector->operator[](0)->BackToGround();
			m_QBertCompVector->operator[](0)->SetFrozen(false);
			m_QBertCompVector->operator[](0)->SetCursesHidden(true);
			m_QBertCompVector->operator[](1)->BackToGround();
			m_QBertCompVector->operator[](1)->SetFrozen(false);
			m_QBertCompVector->operator[](1)->SetCursesHidden(true);

			ChangeSection(m_DeathSceneIdx);
			return false;
		}
		else
		{
			m_DeadQbertP2Timer = 0.f;
			m_DeadQbertP2 = false;
			return true;
		}
	}

	return false;;
}

bool LevelSectionObserver::RoundWonAnimation(const float deltaTime)
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

			if (m_QBertCompVector->operator[](0)->AreGraphicsHidden() == false)
				m_QBertCompVector->operator[](0)->SetHideGraphics(true);
			if (m_QBertCompVector->operator[](1)->AreGraphicsHidden() == false)
				m_QBertCompVector->operator[](1)->SetHideGraphics(true);

			// Set cubes to original turned color
			for (const std::shared_ptr<dae::GameObject>& cube : m_Pyramid->m_CubeGOVector)
			{
				if (m_Level == 2)
					cube->GetComponent<Cube>()->MakeCube3rdColor();
				else
					cube->GetComponent<Cube>()->MakeCube2ndColor();
			}
		}

		m_ClearDisksTimer += deltaTime;
		if (m_ClearDisksTimer >= m_ClearDisksPause)
			return true;
	}
	
	return false;
}
