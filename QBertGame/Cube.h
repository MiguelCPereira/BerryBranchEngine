#pragma once
#include <memory>
#include "BaseComponent.h"


class Cube final : public dae::BaseComponent
{
public:
	explicit Cube(const std::shared_ptr<dae::GameObject>& gameObject);
	~Cube() = default;

	Cube(const Cube& other) = delete;
	Cube(Cube&& other) noexcept = delete;
	Cube& operator=(const Cube& other) = delete;
	Cube& operator=(Cube&& other) noexcept = delete;

	void InvertTurned();

	void Update(const float deltaTime) override;

private:
	std::shared_ptr<dae::GameObject> m_GameObject{};
	bool m_Turned;
};

