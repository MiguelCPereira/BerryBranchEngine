#pragma once
#include "BaseComponent.h"

class InstructionsScreen final : public dae::BaseComponent
{
public:
	explicit InstructionsScreen() = default;
	~InstructionsScreen() override = default;

	void Update(const float deltaTime) override;

	void ChangeScene() const;
};

