#pragma once
#include <vector>


#include "Cube.h"

// The cube indexes are counted from top to bottom, left to right

class Pyramid
{
public:
	Pyramid(float posX, float posY);
	~Pyramid() = default;

	Pyramid(const Pyramid& other) = delete;
	Pyramid(Pyramid&& other) noexcept = delete;
	Pyramid& operator=(const Pyramid& other) = delete;
	Pyramid& operator=(Pyramid&& other) noexcept = delete;

	std::vector<std::shared_ptr<dae::GameObject>> m_CubeGOVector;

private:
	const float m_PosX, m_PosY;
	const int m_TotalCubes;

	void FillCubesGOVector();
};

