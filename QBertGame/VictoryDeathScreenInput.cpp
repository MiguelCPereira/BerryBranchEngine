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


	auto goBackController1 = std::make_unique<GoBackMenuCommand>();
	goBackController1->SetActor(m_MenuComponentGO);
	goBackController1->SetButtonPressType(dae::ButtonPress::PressedDown);
	std::pair<unsigned, dae::ControllerButton> controllerKey(0, dae::ControllerButton::ButtonY);
	dae::InputManager::GetInstance().AddCommand(controllerKey, std::move(goBackController1));


	auto goBackController2 = std::make_unique<GoBackMenuCommand>();
	goBackController2->SetActor(m_MenuComponentGO);
	goBackController2->SetButtonPressType(dae::ButtonPress::PressedDown);
	controllerKey.first = 1;
	dae::InputManager::GetInstance().AddCommand(controllerKey, std::move(goBackController2));
}

void VictoryDeathScreenInput::Update(const float)
{
}