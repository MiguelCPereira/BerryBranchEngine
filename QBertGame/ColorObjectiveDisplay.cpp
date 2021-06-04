#include "ColorObjectiveDisplay.h"
#include "GraphicsComponent.h"


ColorObjectiveDisplay::ColorObjectiveDisplay(dae::GraphicsComponent* graphicsComp, int colorIdx, int level, float spriteWidth, float spriteHeight)
	: m_GraphicsComp(graphicsComp)
	, m_SpriteWidth(spriteWidth)
	, m_SpriteHeight(spriteHeight)
	, m_ColorIdx(colorIdx)
	, m_Level(level)
{
}

ColorObjectiveDisplay::~ColorObjectiveDisplay()
{
	m_GraphicsComp = nullptr;
}


void ColorObjectiveDisplay::Initialize()
{
	UpdateColorIcon();
}

void ColorObjectiveDisplay::Update(const float)
{
}

void ColorObjectiveDisplay::UpdateColorIcon() const
{
	if(m_Level != 2)
		m_GraphicsComp->SetSrcRectangle(m_SpriteWidth * float(m_ColorIdx), 0, m_SpriteWidth, m_SpriteHeight);
	else
		m_GraphicsComp->SetSrcRectangle(m_SpriteWidth * float(m_ColorIdx), m_SpriteHeight, m_SpriteWidth, m_SpriteHeight);
}
