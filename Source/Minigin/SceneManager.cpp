#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Initialize()
{
	m_Scenes[m_CurrentScene]->Initialize();
}

void dae::SceneManager::Update(const float deltaTime)
{
	m_Scenes[m_CurrentScene]->Update(deltaTime);
}

void dae::SceneManager::Render()
{
	m_Scenes[m_CurrentScene]->Render();
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return *scene;
}

void dae::SceneManager::ChangeScene(int newSceneIdx)
{
	if (newSceneIdx < int(m_Scenes.size()))
	{
		m_CurrentScene = newSceneIdx;
		m_Scenes[m_CurrentScene]->Initialize();
	}
	else
		std::cout << "Scene change failed\n";
}
