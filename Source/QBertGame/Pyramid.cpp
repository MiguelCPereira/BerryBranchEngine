#include "Pyramid.h"
#include "QBert.h"
#include "GraphicsComponent.h"
#include "GameObject.h"
#include "Cube.h"

Pyramid::Pyramid(float posX, float posY, int nrRows, float cubesActualWidth, float cubesActualHeight, int colorIdx, int level, float cubeSpriteWidth, float cubeSpriteHeight)
	: m_PosX{ posX }
	, m_PosY{ posY }
	, m_CubesActualWidth{ cubesActualWidth }
	, m_CubesActualHeight{ cubesActualHeight }
	, m_TotalCubes{ nrRows * (nrRows + 1) / 2 }
	, m_NrRows{ nrRows }
	, m_ColorIdx{ colorIdx }
	, m_Level{ level }
	, m_CubeSpriteWidth{ cubeSpriteWidth }
	, m_CubeSpriteHeight{ cubeSpriteHeight }

{
	FillCubesGOVector();
}

void Pyramid::FillCubesGOVector()
{
	float tempPosX = m_PosX;
	float tempPosY = m_PosY;
	int nrRow = 1;
	int cubesInRow = 0;

	for (int i = 0; i < m_TotalCubes; i++)
	{
		auto newCubeGO = std::make_shared<dae::GameObject>();
		newCubeGO->AddComponent(new Cube(newCubeGO, m_ColorIdx, m_Level, m_CubeSpriteWidth, m_CubeSpriteHeight));

		// Make the graphics a blue cube (or yellow for 2nd color, white for 3rd, light-blue for 4th, etc)
		newCubeGO->AddComponent(new dae::GraphicsComponent("QBert Cubes.png", tempPosX, tempPosY, m_CubesActualWidth, m_CubesActualHeight
												, float(m_ColorIdx)* m_CubeSpriteWidth, 0, m_CubeSpriteWidth, m_CubeSpriteHeight));
		
		m_CubeGOVector.push_back(std::move(newCubeGO));
		cubesInRow++;

		tempPosX += m_CubesActualWidth;

		// If all the cubes in said row have been created
		// Skip to the next one (and set the starting position for the next row's first cube)
		if (cubesInRow >= nrRow)
		{
			tempPosY += m_CubesActualHeight * 0.75f;
			tempPosX = m_PosX - (m_CubesActualWidth / 2 * nrRow);
			cubesInRow = 0;
			nrRow++;
		}
	}
}

