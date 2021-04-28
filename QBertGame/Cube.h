#pragma once

class Cube
{
public:
	Cube(float posX, float posY);
	~Cube();

	Cube(const Cube& other) = delete;
	Cube(Cube&& other) noexcept = delete;
	Cube& operator=(const Cube& other) = delete;
	Cube& operator=(Cube&& other) noexcept = delete;
	
	void Draw() const;

	float GetSpriteHeight() const;
	float GetSpriteWeight() const;

private:
	const float m_SpriteHeight, m_SpriteWeight;
	const float m_PosX, m_PosY;
	bool m_Turned;
};

