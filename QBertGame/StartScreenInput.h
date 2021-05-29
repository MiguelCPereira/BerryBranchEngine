#pragma once
#include "BaseComponent.h"
#include <memory>

class StartScreenInput final : public dae::BaseComponent
{
public:
	explicit StartScreenInput(const std::shared_ptr<dae::GameObject>& menuComponentGO);
	~StartScreenInput() override = default;

	void Initialize() override;
	void Update(const float deltaTime) override;

private:
	std::shared_ptr<dae::GameObject> m_MenuComponentGO;
};

