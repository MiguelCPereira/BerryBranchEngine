#include "Cube.h"
#include "QBertComponent.h"

Cube::Cube(const std::shared_ptr<dae::GameObject>& gameObject)
	: m_GameObject(gameObject)
	, m_Turned(false)

{
}

void Cube::InvertTurned()
{
	m_Turned = !m_Turned;
	m_Subject->Notify(dae::Event::ColorChange);
}

void Cube::Update(const float)
{
}