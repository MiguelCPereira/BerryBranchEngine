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
	if (m_ComponentsRemoved == false)
	{
		for (BaseComponent* baseComp : m_Components)
		{
			if (m_ComponentsRemoved)
				break;

			if (baseComp != nullptr)
				baseComp->Initialize();
		}
	}
}

void dae::GameObject::Update(const float deltaTime)
{
	if (m_ComponentsRemoved == false)
	{
		for (BaseComponent* baseComp : m_Components)
		{
			if (m_ComponentsRemoved)
				break;

			if (baseComp != nullptr && m_ComponentsRemoved == false)
				baseComp->Update(deltaTime);
		}
	}
}

void dae::GameObject::Render() const
{
	if (m_ComponentsRemoved == false)
	{
		for (BaseComponent* baseComp : m_Components)
		{
			if (m_ComponentsRemoved)
				break;

			if (baseComp != nullptr && m_ComponentsRemoved == false)
				baseComp->Render();
		}
	}
}

void dae::GameObject::SetPosition(float x, float y) const
{
	m_Transform->SetPosition(x, y, 0.0f);
}

void dae::GameObject::AddComponent(BaseComponent* newComponent)
{
	m_Components.push_back(newComponent);
}

void dae::GameObject::RemoveAllComponents()
{
	// Remove all components from the end to last to the first idx,
	// As to not delete an observed component before their observer
	
	auto nrComponents = int(m_Components.size());
	for (auto i = nrComponents - 1; i >= 0; i--)
	{
		auto* component = m_Components[i];
		delete component;
	}

	//m_Components.clear();
	m_ComponentsRemoved = true;
}
