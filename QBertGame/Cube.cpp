#include "Cube.h"
#include "GameObject.h"
#include "GraphicsComponent.h"

Cube::Cube(const std::shared_ptr<dae::GameObject>& gameObject)
	: m_GameObject(gameObject)
	, m_Turned(false)

{
}

void Cube::TurnCube()
{
	if(m_Turned == false)
		m_GameObject->GetComponent<dae::GraphicsComponent>()->SetTexture("Cube Yellow.png");
	m_Turned = true;
}

void Cube::Update(const float)
{
}