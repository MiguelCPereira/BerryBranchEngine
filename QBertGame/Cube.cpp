#include "Cube.h"

Cube::Cube(float posX, float posY)
	: m_SpriteHeight{ }
	, m_SpriteWeight{ }
	, m_PosX{ posX }
	, m_PosY{ posY }

{
}

Cube::~Cube()
{
}


void Cube::Draw() const
{
}

float Cube::GetSpriteHeight() const
{
	return m_SpriteHeight;
}

float Cube::GetSpriteWeight() const
{
	return m_SpriteWeight;
}