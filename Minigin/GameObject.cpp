#include "MiniginPCH.h"
#include "GameObject.h"
#include "BaseComponent.h"
#include "Transform.h"


dae::GameObject::~GameObject()
{
	for (BaseComponent* baseComp : m_Components)
	{
		delete baseComp;
		baseComp = nullptr;
	}
	
	delete m_Transform;
	m_Transform = nullptr;
}

void dae::GameObject::Initialize()
{
	for (BaseComponent* baseComp : m_Components)
	{
		if (baseComp != nullptr)
			baseComp->Initialize();
	}
}

void dae::GameObject::Update(const float deltaTime)
{
	for (BaseComponent* baseComp : m_Components)
	{
		if (m_ComponentsRemoved)
			break;
		
		if(baseComp != nullptr)
			baseComp->Update(deltaTime);
	}
}

void dae::GameObject::Render() const
{
	for (BaseComponent* baseComp : m_Components)
	{
		if (m_ComponentsRemoved)
			break;
		
		if (baseComp != nullptr)
			baseComp->Render();
	}
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform->SetPosition(x, y, 0.0f);
}

void dae::GameObject::AddComponent(BaseComponent* newComponent)
{
	m_Components.push_back(newComponent);
}

void dae::GameObject::RemoveAllComponents()
{
	for(auto component : m_Components)
	{
		delete component;
		component = nullptr;
	}

	m_ComponentsRemoved = true;
	
	m_Components.clear();
}
