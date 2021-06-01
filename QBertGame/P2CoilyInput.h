#pragma once
#include "BaseComponent.h"
#include <memory>

class P2CoilyInput final : public dae::BaseComponent
{
public:
	explicit P2CoilyInput(const std::shared_ptr<dae::GameObject>& coilyGO);
	~P2CoilyInput() override = default;

	void Initialize() override;
	void Update(const float deltaTime) override;

private:
	std::shared_ptr<dae::GameObject> m_CoilyGO;
};

