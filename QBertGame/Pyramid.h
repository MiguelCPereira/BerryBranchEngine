#pragma once
#include <vector>


#include "Cube.h"

// The cube indexes are counted from top to bottom, left to right

class Pyramid
{
public:
	Pyramid(float posX, float posY);
	~Pyramid();

	Pyramid(const Pyramid& other) = delete;
	Pyramid(Pyramid&& other) noexcept = delete;
	Pyramid& operator=(const Pyramid& other) = delete;
	Pyramid& operator=(Pyramid&& other) noexcept = delete;

	void Draw();

private:
	const float m_PosX, m_PosY;
	const int m_TotalCubes;
	std::vector<Cube*> m_CubeVector;

	void CreateCubes();
};

