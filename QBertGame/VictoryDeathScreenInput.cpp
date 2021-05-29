#include "VictoryDeathScreenInput.h"
#include "GameCommands.h"
#include "InputManager.h"

VictoryDeathScreenInput::VictoryDeathScreenInput(const std::shared_ptr<dae::GameObject>& menuComponentGO)
	: m_MenuComponentGO(menuComponentGO)
{
}

void VictoryDeathScreenInput::Initialize()
{
	dae::InputManager::GetInstance().ClearAllCommands();

	auto goBackKeyboard = std::make_unique<GoBackMenuCommand>();
	goBackKeyboard->SetActor(m_MenuComponentGO);
	goBackKeyboard->SetButtonPressType(dae::ButtonPress::PressedDown);
	dae::InputManager::GetInstance().AddCommand(SDLK_ESCAPE, std::move(goBackKeyboard));


	auto goBackController = std::make_unique<GoBackMenuCommand>();
	goBackController->SetActor(m_MenuComponentGO);
	goBackController->SetButtonPressType(dae::ButtonPress::PressedDown);
	const std::pair<unsigned, dae::ControllerButton> controllerKey(0, dae::ControllerButton::Start);
	dae::InputManager::GetInstance().AddCommand(controllerKey, std::move(goBackController));
}

void VictoryDeathScreenInput::Update(const float)
{
}