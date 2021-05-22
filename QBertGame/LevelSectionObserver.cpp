#include "LevelSectionObserver.h"

#include <iostream>
#include "Cube.h"
#include "QBert.h"
#include "GameObject.h"
#include "GraphicsComponent.h"
#include "Pyramid.h"
#include "SceneManager.h"
#include "SlickSam.h"

LevelSectionObserver::LevelSectionObserver(const std::shared_ptr<dae::GameObject>& gameObject, dae::QBert* qBertComp, Pyramid* pyramid)
	: m_QBertComp(qBertComp)
	, m_Pyramid(pyramid)
	, m_SlickSamCompVector()
	, m_GameObject(gameObject)
	, m_SectionComplete(false)
{}

LevelSectionObserver::LevelSectionObserver(const std::shared_ptr<dae::GameObject>& gameObject, dae::QBert* qBertComp,
	Pyramid* pyramid, std::vector<SlickSam*>* slickSamCompVector)
	: m_QBertComp(qBertComp)
	, m_Pyramid(pyramid)
	, m_SlickSamCompVector(slickSamCompVector)
	, m_GameObject(gameObject)
	, m_SectionComplete(false)
{}

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

	if(m_SlickSamCompVector->empty() == false)
	{
		for (int i = 0; i < m_SlickSamCompVector->size(); i++)
		{
			if (m_SlickSamCompVector->operator[](i) != nullptr)
				m_SlickSamCompVector->operator[](i)->GetSubject()->AddObserver(this);
		}
	}
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
