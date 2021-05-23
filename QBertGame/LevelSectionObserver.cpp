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

LevelSectionObserver::LevelSectionObserver(const std::shared_ptr<dae::GameObject>& gameObject, dae::QBert* qBertComp, Pyramid* pyramid,
	bool spawnSlickSams, float slickSamSpawnInterval, float slickSamMoveInterval)
	: m_QBertComp(qBertComp)
	, m_Pyramid(pyramid)
	, m_GameObject(gameObject)
	, m_SectionComplete(false)
	, m_SpawnSlickSams(spawnSlickSams)
	, m_SlickSamSpawnTimer(0.f)
	, m_SlickSamSpawnInterval(slickSamSpawnInterval)
	, m_SlickSamMoveInterval(slickSamMoveInterval)
{
	m_SlickSamCompVector = new std::vector<SlickSam*>;
}

LevelSectionObserver::~LevelSectionObserver()
{
	if (m_QBertComp != nullptr)
		m_QBertComp->GetSubject()->RemoveObserver(this);

	if (m_SlickSamCompVector->empty() == false)
	{
		for (int i = 0; i < m_SlickSamCompVector->size(); i++)
		{
			if (m_SlickSamCompVector->operator[](i) != nullptr)
				m_SlickSamCompVector->operator[](i)->GetSubject()->RemoveObserver(this);
		}
	}

	delete m_Pyramid;
	m_Pyramid = nullptr;
}

void LevelSectionObserver::Initialize()
{
	if (m_QBertComp != nullptr)
		m_QBertComp->GetSubject()->AddObserver(this);
}

void LevelSectionObserver::SetQBert(dae::QBert* qBertComp)
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

void LevelSectionObserver::SetSlickSamVector(std::vector<SlickSam*>* slickSamCompVector)
{
	if (m_SlickSamCompVector->empty() == false)
	{
		for (int i = 0; i < m_SlickSamCompVector->size(); i++)
		{
			if (m_SlickSamCompVector->operator[](i) != nullptr)
				m_SlickSamCompVector->operator[](i)->GetSubject()->RemoveObserver(this);
		}
	}

	m_SlickSamCompVector = slickSamCompVector;

	if (m_SlickSamCompVector->empty() == false)
	{
		for (int i = 0; i < m_SlickSamCompVector->size(); i++)
		{
			if (m_SlickSamCompVector->operator[](i) != nullptr)
				m_SlickSamCompVector->operator[](i)->GetSubject()->AddObserver(this);
		}
	}
}

void LevelSectionObserver::AddSlickSam(bool isSlick, bool isLeft)
{
	auto newSlickSameGO = MakeSlickSam(isSlick, isLeft, m_SlickSamMoveInterval);
	dae::SceneManager::GetInstance().GetCurrentScene()->Add(newSlickSameGO);
	auto* newSlickSamComp = newSlickSameGO->GetComponent<SlickSam>();

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

void LevelSectionObserver::OnNotify(const dae::Event& event)
{
	switch (event)
	{
	case dae::Event::QBertMove:
		// 1 is subtracted from the idx, because the cubes are numbered from 1 to 28
		// But they're stored counting from 0 in the vector
		m_Pyramid->m_CubeGOVector[m_QBertComp->GetPositionIndex() - 1]->GetComponent<Cube>()->TurnCube();
		
		if (CheckAllCubesTurned())
			WinSection();

		for (int i = 0; i < m_SlickSamCompVector->size(); i++)
		{
			if (m_QBertComp->GetPositionIndex() == m_SlickSamCompVector->operator[](i)->GetPositionIndex())
			{
				auto* deadSlickSam = m_SlickSamCompVector->operator[](i);
				m_SlickSamCompVector->erase(std::find(m_SlickSamCompVector->begin(), m_SlickSamCompVector->end(), deadSlickSam));
				deadSlickSam->Die();
			}
		}
		break;
	case dae::Event::SlickSamMove:
		for (int i = 0; i < m_SlickSamCompVector->size(); i++)
		{			
			m_Pyramid->m_CubeGOVector[m_SlickSamCompVector->operator[](i)->GetPositionIndex() - 1]->GetComponent<Cube>()->SlickSamTurnCube();
			
			if (m_QBertComp->GetPositionIndex() == m_SlickSamCompVector->operator[](i)->GetPositionIndex())
			{
				auto* deadSlickSam = m_SlickSamCompVector->operator[](i);
				m_SlickSamCompVector->erase(std::find(m_SlickSamCompVector->begin(), m_SlickSamCompVector->end(), deadSlickSam));
				deadSlickSam->Die();
			}
		}
		break;
	case dae::Event::SlickSamFell:
		for (int i = 0; i < m_SlickSamCompVector->size(); i++)
		{
			auto* slickSam = m_SlickSamCompVector->operator[](i);
			if (slickSam->GetIsAlive() == false)
			{
				m_SlickSamCompVector->erase(std::find(m_SlickSamCompVector->begin(), m_SlickSamCompVector->end(), slickSam));
				slickSam->Die();
			}
		}
		break;
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

void LevelSectionObserver::WinSection()
{
	if (m_SectionComplete == false)
	{
		m_SectionComplete = true;
		std::cout << "Color Switch!\n";
		m_Subject->Notify(dae::Event::ColorChange);
		m_QBertComp->ResetPosition();
		auto& scene = dae::SceneManager::GetInstance();
		scene.ChangeScene(scene.GetCurrentSceneIdx() + 1);
	}	
}

void LevelSectionObserver::Update(const float deltaTime)
{
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
}
