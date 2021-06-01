#pragma once
#include "BaseComponent.h"
#include <memory>

class SoloVersusP1Input final : public dae::BaseComponent
{
public:
	explicit SoloVersusP1Input(const std::shared_ptr<dae::GameObject>& qBertGO);
	~SoloVersusP1Input() override = default;

	void Initialize() override;
	void Update(const float deltaTime) override;

private:
	std::shared_ptr<dae::GameObject> m_QBertGO;
};

