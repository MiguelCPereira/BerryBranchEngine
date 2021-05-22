#pragma once
#include <memory>
#include "BaseComponent.h"


class Cube final : public dae::BaseComponent
{
public:
	explicit Cube(const std::shared_ptr<dae::GameObject>& gameObject, int colorIdx, int level, float cubeSpriteWidth, float cubeSpriteHeight);
	~Cube() = default;

	Cube(const Cube& other) = delete;
	Cube(Cube&& other) noexcept = delete;
	Cube& operator=(const Cube& other) = delete;
	Cube& operator=(Cube&& other) noexcept = delete;

	void TurnCube();
	void SlickSamTurnCube();
	bool GetIsTurned() const { return m_Turned; }

	void Update(const float deltaTime) override;

private:
	std::shared_ptr<dae::GameObject> m_GameObject{};
	bool m_Turned, m_HalfTurned;
	int m_ColorIdx, m_Level;
	float m_CubeSpriteWidth, m_CubeSpriteHeight;
};

