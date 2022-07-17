#pragma once
#include <memory>
#include <vector>

// The cube indexes are counted from top to bottom, left to right, starting at 1


namespace dae
{
	class GameObject;
}

class Pyramid
{
public:
	Pyramid(float posX, float posY, int nrRows, float cubesActualWidth, float cubesActualHeight, int colorIdx, int level, float cubeSpriteWidth,float cubeSpriteHeight);
	~Pyramid() = default;

	Pyramid(const Pyramid& other) = delete;
	Pyramid(Pyramid&& other) noexcept = delete;
	Pyramid& operator=(const Pyramid& other) = delete;
	Pyramid& operator=(Pyramid&& other) noexcept = delete;

	std::vector<std::shared_ptr<dae::GameObject>> m_CubeGOVector;

private:
	const float m_PosX, m_PosY;
	const float m_CubesActualWidth, m_CubesActualHeight;
	const int m_TotalCubes;
	const int m_NrRows;
	const int m_ColorIdx, m_Level;
	const float m_CubeSpriteWidth, m_CubeSpriteHeight;

	void FillCubesGOVector();
};

