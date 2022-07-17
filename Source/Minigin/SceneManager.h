#pragma once
#include "Singleton.h"
#include "MiniginLibType.h"
#include <vector>
#include <memory>
#include <string>

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene MINIGIN_ENTRY& CreateScene(const std::string& name);

		void Initialize();
		void Update(const float deltaTime);
		void Render();

		std::shared_ptr<Scene> GetCurrentScene() const { return m_Scenes[m_CurrentScene]; }
		int GetCurrentSceneIdx() const { return m_CurrentScene;  }
		void MINIGIN_ENTRY ChangeScene(int newSceneIdx);
	
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		int m_CurrentScene = 0;
	};
}
