#pragma once
#include "BaseComponent.h"

namespace dae
{
	class GraphicsComponent;
}

class ColorObjectiveDisplay : public dae::BaseComponent
{
public:
	explicit ColorObjectiveDisplay(dae::GraphicsComponent* graphicsComp, int colorIdx, int level, float spriteWidth, float spriteHeight);
	~ColorObjectiveDisplay() override;

	ColorObjectiveDisplay(const ColorObjectiveDisplay& other) = delete;
	ColorObjectiveDisplay(ColorObjectiveDisplay&& other) noexcept = delete;
	ColorObjectiveDisplay& operator=(const ColorObjectiveDisplay& other) = delete;
	ColorObjectiveDisplay& operator=(ColorObjectiveDisplay&& other) noexcept = delete;

	void Initialize() override;
	void Update(const float deltaTime) override;

	void UpdateColorIcon() const;

private:
	dae::GraphicsComponent* m_GraphicsComp;
	const int m_ColorIdx, m_Level;
	const float m_SpriteWidth, m_SpriteHeight;
};

