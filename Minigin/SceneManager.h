#pragma once
#include "Singleton.h"
#include <vector>

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);

		void Initialize();
		void Update(const float deltaTime);
		void Render();

		int GetCurrentSceneIdx() const { return m_CurrentScene;  }
		void ChangeScene(int newSceneIdx);
	
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		int m_CurrentScene = 0;
	};
}
