#include "LevelTransition.h"

LevelTransition::LevelTransition(const std::shared_ptr<dae::GameObject>& gameObject, float transitionTime)
	: m_GameObject(gameObject)
	, m_TransitionTime(transitionTime)
	, m_Counter(0.f)
{
}

void LevelTransition::Update(const float deltaTime)
{
	m_Counter += deltaTime;

	if(m_Counter >= m_TransitionTime)
	{
		//auto& scene = dae::SceneManager::GetInstance();
		//scene.ChangeScene(scene.GetCurrentSceneIdx() + 1);
	}
}
