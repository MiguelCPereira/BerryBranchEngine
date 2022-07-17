#pragma once
#include "BaseComponent.h"
#include <string>
#include <memory>

namespace dae
{
	class Texture2D;
	class GraphicsComponent final : public BaseComponent
	{
	public:
		MINIGIN_ENTRY GraphicsComponent();
		MINIGIN_ENTRY GraphicsComponent(const std::string& imageFile);
		MINIGIN_ENTRY GraphicsComponent(const std::string& imageFile, float x, float y, float width = 0, float height = 0, float srcX = 0, float srcY = 0, float srcWidth = 0, float srcHeight = 0);
		~GraphicsComponent() = default;

		GraphicsComponent(const GraphicsComponent& other) = delete;
		GraphicsComponent(GraphicsComponent&& other) = delete;
		GraphicsComponent& operator=(const GraphicsComponent& other) = delete;
		GraphicsComponent& operator=(GraphicsComponent&& other) = delete;

		void Update(const float deltaTime) override;
		void Render() const override;
		void MINIGIN_ENTRY SetPosition(float x, float y);
		void MINIGIN_ENTRY SetSize(float width, float height);
		void MINIGIN_ENTRY SetTexture(const std::string& imageFile);
		void MINIGIN_ENTRY SetSrcRectangle(float x, float y, float width, float height);
		void MINIGIN_ENTRY SetHidden(bool isHidden);

		float GetPosX() { return m_PosX; }
		float GetPosY() { return m_PosY; }
		float GetWidth() { return m_Width; }
		float GetHeight() { return m_Height; }

	private:
		std::shared_ptr<Texture2D> m_Texture;
		float m_PosX, m_PosY, m_Width, m_Height;
		float m_SrcX, m_SrcY, m_SrcWidth, m_SrcHeight;
		bool m_Hidden;
	};
}