#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<GameObject>& object, bool renderPriority)
{
	//m_Objects.insert({ object, renderPriority });
	if(renderPriority == false)
		m_Objects.push_back(object);
	else
		m_ObjectsPriority.push_back(object);
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

	for (size_t i = 0; i < m_ObjectsPriority.size(); i++)
	{
		if (m_ObjectsPriority.size() > i)
		{
			if (m_ObjectsPriority[i] != nullptr)
				m_ObjectsPriority[i]->Initialize();
		}
	}

	/*for (const auto& pair : m_Objects)
	{
		if (pair.first != nullptr)
			pair.first->Initialize();
	}*/
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

	for (size_t i = 0; i < m_ObjectsPriority.size(); i++)
	{
		if (m_ObjectsPriority.size() > i)
		{
			if (m_ObjectsPriority[i] != nullptr)
				m_ObjectsPriority[i]->Update(deltaTime);
		}
	}

	/*for (const auto& pair : m_Objects)
	{
		if(pair.first != nullptr)
			pair.first->Update(deltaTime);
	}*/
}

void Scene::Render() const
{
	// Render objects without priority
	for (const auto& object : m_Objects)
	{
		if (object != nullptr)
			object->Render();
	}

	// And render objects with priority afterwards
	for (const auto& object : m_ObjectsPriority)
	{
		if (object != nullptr)
			object->Render();
	}

	
	//// Render objects without priority
	//for (const auto& pair : m_Objects)
	//{
	//	if (pair.first != nullptr && pair.second == false)
	//		pair.first->Render();
	//}

	//// Render objects with priority afterwards
	//for (const auto& pair : m_Objects)
	//{
	//	if (pair.first != nullptr && pair.second == true)
	//		pair.first->Render();
	//}
}

