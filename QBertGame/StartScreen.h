#pragma once
#include "BaseComponent.h"

namespace dae
{
	class GraphicsComponent;
}

class StartScreen final : public dae::BaseComponent
{
public:
	explicit StartScreen(int soloModeSceneIdx, int coopModeSceneIdx, int versusModeSceneIdx, dae::GraphicsComponent* selectionGraphics, float buttonDistance);
	~StartScreen() override = default;

	StartScreen(const StartScreen& other) = delete;
	StartScreen(StartScreen&& other) = delete;
	StartScreen& operator=(const StartScreen& other) = delete;
	StartScreen& operator=(StartScreen&& other) = delete;

	void Update(const float deltaTime) override;

	void ChangeSelection(bool up);
	void StartGame() const;

private:
	dae::GraphicsComponent* m_SelectionGraphics;
	const float m_ButtonDistance;
	int m_Selection;
	const int  m_SoloModeSceneIdx;
	const int  m_CoopModeSceneIdx;
	const int  m_VersusModeSceneIdx;
};

