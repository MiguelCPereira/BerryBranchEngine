#pragma once
#include "BaseComponent.h"
#include <memory>

class PlayerTwoCoilyInput final : public dae::BaseComponent
{
public:
	explicit PlayerTwoCoilyInput(const std::shared_ptr<dae::GameObject>& coilyGO);
	~PlayerTwoCoilyInput() override = default;

	void Initialize() override;
	void Update(const float deltaTime) override;

private:
	std::shared_ptr<dae::GameObject> m_CoilyGO;
};

