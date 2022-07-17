#pragma once
#include "BaseComponent.h"
#include <memory>

class StartScreenInput final : public dae::BaseComponent
{
public:
	explicit StartScreenInput(const std::shared_ptr<dae::GameObject>& menuComponentGO);
	~StartScreenInput() override = default;

	StartScreenInput(const StartScreenInput& other) = delete;
	StartScreenInput(StartScreenInput&& other) noexcept = delete;
	StartScreenInput& operator=(const StartScreenInput& other) = delete;
	StartScreenInput& operator=(StartScreenInput&& other) noexcept = delete;

	void Initialize() override;
	void Update(const float deltaTime) override;

private:
	std::shared_ptr<dae::GameObject> m_MenuComponentGO;
};

