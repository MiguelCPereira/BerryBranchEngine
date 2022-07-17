#pragma once
#include "SceneManager.h"
#include "MiniginLibType.h"
#include <string>

namespace dae
{
	class GameObject;
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void MINIGIN_ENTRY Add(const std::shared_ptr<GameObject>& object, bool renderPriority = false);
		void MINIGIN_ENTRY Initialize();
		void Update(const float deltaTime);
		void Render() const;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);

		std::string m_Name;
		std::vector <std::shared_ptr<GameObject>> m_Objects{};
		std::vector <std::shared_ptr<GameObject>> m_ObjectsPriority{};

		static unsigned int m_IdCounter; 
	};

}
