#pragma once
#include "BaseComponent.h"

class VictoryDeathScreen final : public dae::BaseComponent
{
public:
	explicit VictoryDeathScreen(int startMenuSceneIdx);
	~VictoryDeathScreen() override = default;

	VictoryDeathScreen(const VictoryDeathScreen& other) = delete;
	VictoryDeathScreen(VictoryDeathScreen&& other) = delete;
	VictoryDeathScreen& operator=(const VictoryDeathScreen& other) = delete;
	VictoryDeathScreen& operator=(VictoryDeathScreen&& other) = delete;

	void Update(const float deltaTime) override;

	void GoBack() const;

private:
	const int m_StartMenuSceneIdx;
};


