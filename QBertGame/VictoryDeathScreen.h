#pragma once
#include "BaseComponent.h"

class VictoryDeathScreen final : public dae::BaseComponent
{
public:
	explicit VictoryDeathScreen(int startMenuSceneIdx);
	~VictoryDeathScreen() override = default;

	void Update(const float deltaTime) override;

	void GoBack() const;

private:
	const int m_StartMenuSceneIdx;
};


