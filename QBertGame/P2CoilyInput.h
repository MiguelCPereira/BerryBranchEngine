#pragma once
#include "BaseComponent.h"
#include <memory>

class Coily;

class P2CoilyInput final : public dae::BaseComponent, public dae::Observer
{
public:
	explicit P2CoilyInput(const std::shared_ptr<dae::GameObject>& coilyGO);
	~P2CoilyInput() override;

	P2CoilyInput(const P2CoilyInput& other) = delete;
	P2CoilyInput(P2CoilyInput&& other) noexcept = delete;
	P2CoilyInput& operator=(const P2CoilyInput& other) = delete;
	P2CoilyInput& operator=(P2CoilyInput&& other) noexcept = delete;

	void ClearInput() const;
	
	void Initialize() override;
	void OnNotify(const dae::Event& event) override;
	void Update(const float deltaTime) override;

private:
	std::shared_ptr<dae::GameObject> m_CoilyGO;
	Coily* m_CoilyComp;
	bool m_Deactivated;
};

