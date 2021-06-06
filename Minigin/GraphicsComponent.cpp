#include "MiniginPCH.h"
#include "GraphicsComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Texture2D.h"

dae::GraphicsComponent::GraphicsComponent()
	: m_Texture(nullptr)
	, m_PosX()
	, m_PosY()
	, m_Width()
	, m_Height()
	, m_SrcX()
	, m_SrcY()
	, m_SrcWidth()
	, m_SrcHeight()
	, m_Hidden(false)
{}

dae::GraphicsComponent::GraphicsComponent(const std::string& imageFile)
	: m_PosX()
	, m_PosY()
	, m_Width()
	, m_Height()
	, m_SrcX()
	, m_SrcY()
	, m_SrcWidth()
	, m_SrcHeight()
	, m_Hidden(false)

{
	SetTexture(imageFile);
}

dae::GraphicsComponent::GraphicsComponent(const std::string& imageFile, float x, float y, float width, float height,
	float srcX, float srcY, float srcWidth, float srcHeight)
	: m_PosX(x)
	, m_PosY(y)
	, m_Width(width)
	, m_Height(height)
	, m_SrcX(srcX)
	, m_SrcY(srcY)
	, m_SrcWidth(srcWidth)
	, m_SrcHeight(srcHeight)
	, m_Hidden(false)
{
	SetTexture(imageFile);
}

void dae::GraphicsComponent::Update(const float)
{}

void dae::GraphicsComponent::Render() const
{
	if (m_Hidden == false)
	{
		if (m_SrcWidth > 0 && m_SrcHeight > 0)
		{
			Renderer::GetInstance().RenderTexture(*m_Texture, m_PosX, m_PosY, m_Width, m_Height, m_SrcX, m_SrcY, m_SrcWidth, m_SrcHeight);
		}
		else
		{
			if (m_Width > 0 && m_Height > 0)
				Renderer::GetInstance().RenderTexture(*m_Texture, m_PosX, m_PosY, m_Width, m_Height);
			else
				Renderer::GetInstance().RenderTexture(*m_Texture, m_PosX, m_PosY);
		}
	}
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

void dae::GraphicsComponent::SetSrcRectangle(float x, float y, float width, float height)
{
	m_SrcX = x;
	m_SrcY = y;
	m_SrcWidth = width;
	m_SrcHeight = height;
}

void dae::GraphicsComponent::SetHidden(bool isHidden)
{
	m_Hidden = isHidden;
}

