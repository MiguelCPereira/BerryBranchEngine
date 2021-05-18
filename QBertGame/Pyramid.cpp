#include "Pyramid.h"

#include "GraphicsComponent.h"
#include "GameObject.h"

Pyramid::Pyramid(float posX, float posY)
	: m_PosX{ posX }
	, m_PosY{ posY }
	, m_TotalCubes{ 28 }

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
		newCubeGO->AddComponent(new Cube(newCubeGO));
		newCubeGO->AddComponent(new dae::GraphicsComponent("Cube Blue.png", tempPosX, tempPosY, 56, 56));
		
		m_CubeGOVector.push_back(newCubeGO);
		cubesInRow++;

		auto cubeGraphicsComp = newCubeGO->GetComponent<dae::GraphicsComponent>();
		tempPosX += cubeGraphicsComp->GetWidth();

		// If all the cubes in said row have been created
		// Skip to the next one (and set the starting position for the next row's first cube)
		if (cubesInRow >= nrRow)
		{
			tempPosY += cubeGraphicsComp->GetHeight() * 0.75f;
			tempPosX = m_PosX - (cubeGraphicsComp->GetWidth() / 2 * nrRow);
			cubesInRow = 0;
			nrRow++;
		}
	}
}

