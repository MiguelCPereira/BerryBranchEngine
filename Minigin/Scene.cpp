#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.push_back(object);
}

void Scene::Initialize()
{
	for (size_t i = 0; i < m_Objects.size(); i++)
	{
		if (m_Objects.size() > i)
		{
			if (m_Objects[i] != nullptr)
				m_Objects[i]->Initialize();
		}
	}
}

void Scene::Update(const float deltaTime)
{
	for(size_t i = 0; i < m_Objects.size(); i++)
	{
		if (m_Objects.size() > i)
		{
			if (m_Objects[i] != nullptr)
				m_Objects[i]->Update(deltaTime);
		}
	}
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		if (object != nullptr)
			object->Render();
	}
}

