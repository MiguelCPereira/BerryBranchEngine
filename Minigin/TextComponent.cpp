#include "MiniginPCH.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "Transform.h"

dae::TextComponent::TextComponent(const std::string& text, const std::shared_ptr<Font>& font)
	: m_NeedsUpdate(true)
	, m_Text(text)
	, m_Transform(new Transform())
	, m_Font(font)
	, m_Texture(nullptr)
	, m_ColorR(255)
	, m_ColorG(255)
	, m_ColorB(255)
{ }

dae::TextComponent::TextComponent(const std::string& text, const std::shared_ptr<Font>& font, int colorR, int colorG, int colorB)
	: m_NeedsUpdate(true)
	, m_Text(text)
	, m_Transform(new Transform())
	, m_Font(font)
	, m_Texture(nullptr)
	, m_ColorR(colorR)
	, m_ColorG(colorG)
	, m_ColorB(colorB)
{ }

void dae::TextComponent::Update(const float)
{
	SDL_Color color{ Uint8(m_ColorR),Uint8(m_ColorG),Uint8(m_ColorB) };
	
	if (m_NeedsUpdate)
	{
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_Texture = std::make_shared<Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}

void dae::TextComponent::Render() const
{
	if (m_Texture != nullptr)
	{
		const auto& pos = m_Transform->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
}

// This implementation uses the "dirty flag" pattern
void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void dae::TextComponent::SetPosition(const float x, const float y) const
{
	m_Transform->SetPosition(x, y, 0.0f);
}

