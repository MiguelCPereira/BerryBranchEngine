#pragma once
#include "BaseComponent.h"
#include <memory>

class CoopAllInput final : public dae::BaseComponent
{
public:
	explicit CoopAllInput(const std::shared_ptr<dae::GameObject>& qBert1GO, const std::shared_ptr<dae::GameObject>& qBert2GO);
	~CoopAllInput() override = default;

	CoopAllInput(const CoopAllInput& other) = delete;
	CoopAllInput(CoopAllInput&& other) noexcept = delete;
	CoopAllInput& operator=(const CoopAllInput& other) = delete;
	CoopAllInput& operator=(CoopAllInput&& other) noexcept = delete;

	void Initialize() override;
	void Update(const float deltaTime) override;

private:
	std::shared_ptr<dae::GameObject> m_QBert1GO;
	std::shared_ptr<dae::GameObject> m_QBert2GO;
};

