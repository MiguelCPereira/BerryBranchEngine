#pragma once
#include "SceneObject.h"
#include "Transform.h"

namespace dae
{
	//class BaseComponent;
	class HPTextComponent;
	class FPSComponent;
	class Font;
	class Texture2D;
	class TextObject final : public SceneObject
	{
	public:
		void Update(const float deltaTime) override;
		void Render() const override;

		void SetText(const std::string& text);
		void SetPosition(float x, float y);

		explicit TextObject(const std::string& text, const std::shared_ptr<Font>& font);
		//explicit TextObject(const std::string& text, const std::shared_ptr<Font>& font, BaseComponent* component);
		explicit TextObject(const std::string& text, const std::shared_ptr<Font>& font, FPSComponent* component);
		explicit TextObject(const std::string& text, const std::shared_ptr<Font>& font, HPTextComponent* component);
		virtual ~TextObject();
		TextObject(const TextObject& other) = delete;
		TextObject(TextObject&& other) = delete;
		TextObject& operator=(const TextObject& other) = delete;
		TextObject& operator=(TextObject&& other) = delete;
	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		Transform m_Transform;
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_Texture;
		//BaseComponent* m_TextComponent;
		FPSComponent* m_FPSComponent;
		HPTextComponent* m_HPTextComponent;

	};
}