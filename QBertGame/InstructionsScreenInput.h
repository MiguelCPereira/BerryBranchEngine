#pragma once
#include "BaseComponent.h"
#include <memory>

class InstructionsScreenInput final : public dae::BaseComponent
{
public:
	explicit InstructionsScreenInput(const std::shared_ptr<dae::GameObject>& instructionsComponentGO);
	~InstructionsScreenInput() override = default;

	void Initialize() override;
	void Update(const float deltaTime) override;

private:
	std::shared_ptr<dae::GameObject> m_InstructionsComponentGO;
};

