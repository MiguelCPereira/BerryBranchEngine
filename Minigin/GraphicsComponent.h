#pragma once
#include "BaseComponent.h"
#include <string>

namespace dae
{
	class Texture2D;
	class GraphicsComponent final : public BaseComponent
	{
	public:
		GraphicsComponent();
		GraphicsComponent(const std::string& imageFile);
		//GraphicsComponent(const std::string& imageFile, float x, float y, float width = 0, float height = 0);
		GraphicsComponent(const std::string& imageFile, float x, float y, float width = 0, float height = 0, float srcX = 0, float srcY = 0, float srcWidth = 0, float srcHeight = 0);
		~GraphicsComponent() = default;

		GraphicsComponent(const GraphicsComponent& other) = delete;
		GraphicsComponent(GraphicsComponent&& other) = delete;
		GraphicsComponent& operator=(const GraphicsComponent& other) = delete;
		GraphicsComponent& operator=(GraphicsComponent&& other) = delete;

		void Update(const float deltaTime) override;
		void Render() const override;
		void SetPosition(float x, float y);
		void SetSize(float width, float height);
		void SetTexture(const std::string& imageFile);
		void SetSrcRectangle(float x, float y, float width, float height);

		float GetPosX() { return m_PosX; }
		float GetPosY() { return m_PosY; }
		float GetWidth() { return m_Width; }
		float GetHeight() { return m_Height; }

	private:
		std::shared_ptr<Texture2D> m_Texture;
		float m_PosX{}, m_PosY{}, m_Width{}, m_Height{};
		float m_SrcX{}, m_SrcY{}, m_SrcWidth{}, m_SrcHeight{};
	};
}