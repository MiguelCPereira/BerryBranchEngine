#pragma once
#include "BaseComponent.h"

namespace dae
{
	class Texture2D;
	class GraphicsComponent final : public BaseComponent
	{
	public:
		GraphicsComponent();
		GraphicsComponent(const std::string& imageFile);
		GraphicsComponent(const std::string& imageFile, float x, float y, float width = 0, float height = 0);
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

	private:
		std::shared_ptr<Texture2D> m_Texture;
		float m_PosX{}, m_PosY{}, m_Width{}, m_Height{};
	};
}