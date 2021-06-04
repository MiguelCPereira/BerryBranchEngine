#pragma once
#include "BaseComponent.h"
#include <memory>

namespace dae
{
	class Texture2D;
	class Font;
	class Transform;

	class TextComponent final : public BaseComponent
	{
	public:
		void Update(const float deltaTime) override;
		void Render() const override;

		MINIGIN_ENTRY void SetText(const std::string& text);
		MINIGIN_ENTRY void SetPosition(float x, float y) const;

		explicit MINIGIN_ENTRY TextComponent(const std::string& text, const std::shared_ptr<Font>& font);
		explicit MINIGIN_ENTRY TextComponent(const std::string& text, const std::shared_ptr<Font>& font, int colorR, int colorG, int colorB);
		virtual ~TextComponent() = default;
		
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;
	
	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		Transform* m_Transform;
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_Texture;
		int m_ColorR, m_ColorG, m_ColorB;
	};
}

