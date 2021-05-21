#include "MainObserver.h"

#include <iostream>


#include "Cube.h"
#include "QBert.h"
#include "GameObject.h"
#include "Pyramid.h"

MainObserver::MainObserver(const std::shared_ptr<dae::GameObject>& gameObject, dae::QBert* qBertComp, Pyramid* pyramid)
	: m_QBertComp(qBertComp)
	, m_Pyramid(pyramid)
	, m_GameObject(gameObject)
	, m_LevelComplete(false)
{}

MainObserver::~MainObserver()
{
	if (m_QBertComp != nullptr)
		m_QBertComp->GetSubject()->RemoveObserver(this);

	delete m_Pyramid;
	m_Pyramid = nullptr;
}

void MainObserver::Initialize()
{
	if (m_QBertComp != nullptr)
		m_QBertComp->GetSubject()->AddObserver(this);
}

void MainObserver::SetQBert(dae::QBert* qBertComp)
{
	if (m_QBertComp != nullptr)
		m_QBertComp->GetSubject()->RemoveObserver(this);

	m_QBertComp = qBertComp;

	if (m_QBertComp != nullptr)
		m_QBertComp->GetSubject()->AddObserver(this);
}

void MainObserver::SetPyramid(Pyramid* pyramid)
{
	delete m_Pyramid;
	m_Pyramid = nullptr;
	m_Pyramid = pyramid;
}

void MainObserver::OnNotify(const dae::Event& event)
{
	switch (event)
	{
	case dae::Event::QBertMove:
		const auto qBertIdx = m_QBertComp->GetPositionIndex();
		// 1 is subtracted from the idx, because the cubes are numbered from 1 to 28
		// But they're stored counting from 0 in the vector
		m_Pyramid->m_CubeGOVector[qBertIdx - 1]->GetComponent<Cube>()->TurnCube();
		if (CheckAllCubesTurned())
			WinLevel();
		break;
	}
}

bool MainObserver::CheckAllCubesTurned() const
{
	for(const std::shared_ptr<dae::GameObject>& cube : m_Pyramid->m_CubeGOVector)
	{
		if (cube->GetComponent<Cube>()->GetIsTurned() == false)
			return false;
	}
	
	return true;
}

void MainObserver::WinLevel()
{
	if (m_LevelComplete == false)
	{
		m_LevelComplete = true;
		std::cout << "Level complete!\n";
	}
}
