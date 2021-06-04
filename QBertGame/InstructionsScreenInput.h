#pragma once
#include "BaseComponent.h"
#include <memory>

class InstructionsScreenInput final : public dae::BaseComponent
{
public:
	explicit InstructionsScreenInput(const std::shared_ptr<dae::GameObject>& instructionsComponentGO);
	~InstructionsScreenInput() override = default;

	InstructionsScreenInput(const InstructionsScreenInput& other) = delete;
	InstructionsScreenInput(InstructionsScreenInput&& other) noexcept = delete;
	InstructionsScreenInput& operator=(const InstructionsScreenInput& other) = delete;
	InstructionsScreenInput& operator=(InstructionsScreenInput&& other) noexcept = delete;

	void Initialize() override;
	void Update(const float deltaTime) override;

private:
	std::shared_ptr<dae::GameObject> m_InstructionsComponentGO;
};

