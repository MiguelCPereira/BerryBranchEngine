#include "MiniginPCH.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "TextObject.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "FPSComponent.h"

dae::TextObject::TextObject(const std::string& text, const std::shared_ptr<Font>& font)
	: m_NeedsUpdate(true), m_Text(text), m_Font(font), m_Texture(nullptr), m_FPSComponent(nullptr)
{ }

dae::TextObject::TextObject(const std::string& text, const std::shared_ptr<Font>& font, FPSComponent* component)
	: m_NeedsUpdate(true), m_Text(text), m_Font(font), m_Texture(nullptr), m_FPSComponent(component)
{ }

void dae::TextObject::Update(const float deltaTime)
{
	SDL_Color color;
	
	if (m_FPSComponent != nullptr)
	{
		m_FPSComponent->Update(*this, deltaTime);
	}
	
	if (m_NeedsUpdate)
	{
		if (m_FPSComponent != nullptr) { color = { 255,255,0 }; }
		else { color = { 255,255,255 }; }
		
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

void dae::TextObject::Render() const
{
	if (m_Texture != nullptr)
	{
		const auto pos = m_Transform.GetPosition();
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
}

// This implementation uses the "dirty flag" pattern
void dae::TextObject::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void dae::TextObject::SetPosition(const float x, const float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}


