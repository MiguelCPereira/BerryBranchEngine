#pragma once
#include "BaseComponent.h"

class InstructionsScreen final : public dae::BaseComponent
{
public:
	explicit InstructionsScreen() = default;
	~InstructionsScreen() override = default;

	InstructionsScreen(const InstructionsScreen& other) = delete;
	InstructionsScreen(InstructionsScreen&& other) = delete;
	InstructionsScreen& operator=(const InstructionsScreen& other) = delete;
	InstructionsScreen& operator=(InstructionsScreen&& other) = delete;

	void Update(const float deltaTime) override;

	void ChangeScene() const;
};

