#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"


dae::GameObject::~GameObject()
{
	for (BaseComponent* baseComp : m_Components)
	{
		delete baseComp;
		baseComp = nullptr;
	}
}

void dae::GameObject::Initialize()
{
	for (BaseComponent* baseComp : m_Components)
	{
		baseComp->Initialize();
	}
}

void dae::GameObject::Update(const float deltaTime)
{
	for (BaseComponent* baseComp : m_Components)
	{
		baseComp->Update(*this, m_Transform, m_Texture, deltaTime);
	}
}

void dae::GameObject::Render() const
{
	const auto pos = m_Transform.GetPosition();
	Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
}

void dae::GameObject::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}
