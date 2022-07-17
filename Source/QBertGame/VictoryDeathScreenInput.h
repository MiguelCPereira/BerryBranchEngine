#pragma once
#include "BaseComponent.h"
#include <memory>

class VictoryDeathScreenInput final : public dae::BaseComponent
{
public:
	explicit VictoryDeathScreenInput(const std::shared_ptr<dae::GameObject>& menuComponentGO);
	~VictoryDeathScreenInput() override = default;

	VictoryDeathScreenInput(const VictoryDeathScreenInput& other) = delete;
	VictoryDeathScreenInput(VictoryDeathScreenInput&& other) noexcept = delete;
	VictoryDeathScreenInput& operator=(const VictoryDeathScreenInput& other) = delete;
	VictoryDeathScreenInput& operator=(VictoryDeathScreenInput&& other) noexcept = delete;

	void Initialize() override;
	void Update(const float deltaTime) override;

private:
	std::shared_ptr<dae::GameObject> m_MenuComponentGO;
};

