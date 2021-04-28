#include "Pyramid.h"

Pyramid::Pyramid(float posX, float posY)
	: m_PosX{ posX }
	, m_PosY{ posY }
	, m_TotalCubes{ 28 }

{
	CreateCubes();
}

Pyramid::~Pyramid()
{
}


void Pyramid::CreateCubes()
{
	float tempPosX = m_PosX;
	float tempPosY = m_PosY;
	int nrRow = 1;
	int cubesInRow = 0;

	for (int i = 0; i < m_TotalCubes; i++)
	{
		auto* newCube = new Cube(tempPosX, tempPosY);
		m_CubeVector.push_back(newCube);
		cubesInRow++;

		// If all the cubes in said row have been created, skip to the next one (and set the starting position for the next row's first cube)
		if (cubesInRow >= nrRow)
		{
			tempPosY -= newCube->GetSpriteHeight();
			tempPosX = m_PosX - (newCube->GetSpriteWeight() / 2 * nrRow);
			cubesInRow = 0;
			nrRow++;
		}
	}
}

void Pyramid::Draw()
{
	for( auto* cube : m_CubeVector)
	{
		cube->Draw();
	}
}

