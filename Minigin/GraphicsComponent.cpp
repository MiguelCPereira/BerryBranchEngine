#include "MiniginPCH.h"
#include "GraphicsComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Texture2D.h"

dae::GraphicsComponent::GraphicsComponent()
	:m_Texture(nullptr)
{}

dae::GraphicsComponent::GraphicsComponent(const std::string& imageFile)
{
	SetTexture(imageFile);
}

dae::GraphicsComponent::GraphicsComponent(const std::string& imageFile, float x, float y, float width, float height)
	: m_PosX{x},
	m_PosY{y},
	m_Width(width),
	m_Height(height)
{
	SetTexture(imageFile);
}

void dae::GraphicsComponent::Update(const float)
{}

void dae::GraphicsComponent::Render() const
{
	if (m_Width > 0 && m_Height > 0)
		Renderer::GetInstance().RenderTexture(*m_Texture, m_PosX, m_PosY, m_Width, m_Height);
	else
		Renderer::GetInstance().RenderTexture(*m_Texture, m_PosX, m_PosY);
}

void dae::GraphicsComponent::SetPosition(float x, float y)
{
	m_PosX = x;
	m_PosY = y;
}

void dae::GraphicsComponent::SetSize(float w, float h)
{
	m_Width = w;
	m_Height = h;
}

void dae::GraphicsComponent::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

