#pragma once
#include <memory>
#include <vector>

// The cube indexes are counted from top to bottom, left to right


namespace dae
{
	class GameObject;
}

class Pyramid
{
public:
	Pyramid(float posX, float posY, int nrRows, float cubesWidth, float cubesHeight);
	~Pyramid() = default;

	Pyramid(const Pyramid& other) = delete;
	Pyramid(Pyramid&& other) noexcept = delete;
	Pyramid& operator=(const Pyramid& other) = delete;
	Pyramid& operator=(Pyramid&& other) noexcept = delete;

	std::vector<std::shared_ptr<dae::GameObject>> m_CubeGOVector;

private:
	const float m_PosX, m_PosY;
	const float m_CubesWidth, m_CubesHeight;
	const int m_TotalCubes;
	const int m_NrRows;

	void FillCubesGOVector();
};

