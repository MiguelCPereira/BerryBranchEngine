#pragma once
#include <memory>
#include "BaseComponent.h"

class LevelTransition final : public dae::BaseComponent
{
public:
	explicit LevelTransition(const std::shared_ptr<dae::GameObject>& gameObject, float transitionTime);
	~LevelTransition() = default;

	LevelTransition(const LevelTransition& other) = delete;
	LevelTransition(LevelTransition&& other) noexcept = delete;
	LevelTransition& operator=(const LevelTransition& other) = delete;
	LevelTransition& operator=(LevelTransition&& other) noexcept = delete;

	void Update(const float deltaTime) override;

private:
	std::shared_ptr<dae::GameObject> m_GameObject{};
	float m_TransitionTime, m_Counter;
};
