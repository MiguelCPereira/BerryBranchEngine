#pragma once
#include "BaseComponent.h"
#include <memory>

class PlayerOneInput final : public dae::BaseComponent
{
public:
	explicit PlayerOneInput(const std::shared_ptr<dae::GameObject>& qBertGO);
	~PlayerOneInput() override = default;

	void Initialize() override;
	void Update(const float deltaTime) override;

private:
	std::shared_ptr<dae::GameObject> m_QBertGO;
};

