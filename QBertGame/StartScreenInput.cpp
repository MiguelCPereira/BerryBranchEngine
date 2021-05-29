#include "StartScreenInput.h"
#include "GameCommands.h"
#include "InputManager.h"

StartScreenInput::StartScreenInput(const std::shared_ptr<dae::GameObject>& menuComponentGO)
	: m_MenuComponentGO(menuComponentGO)
{
}

void StartScreenInput::Initialize()
{
	dae::InputManager::GetInstance().ClearAllCommands();
	
	auto selectSpaceKeyboard = std::make_unique<SelectMenuCommand>();
	selectSpaceKeyboard->SetActor(m_MenuComponentGO);
	selectSpaceKeyboard->SetButtonPressType(dae::ButtonPress::PressedDown);
	dae::InputManager::GetInstance().AddCommand(SDLK_SPACE, std::move(selectSpaceKeyboard));

	auto moveUpWMenuKeyboard = std::make_unique<MoveUpMenuCommand>();
	moveUpWMenuKeyboard->SetActor(m_MenuComponentGO);
	moveUpWMenuKeyboard->SetButtonPressType(dae::ButtonPress::PressedDown);
	dae::InputManager::GetInstance().AddCommand(SDLK_w, std::move(moveUpWMenuKeyboard));

	auto moveDownSMenuKeyboard = std::make_unique<MoveDownMenuCommand>();
	moveDownSMenuKeyboard->SetActor(m_MenuComponentGO);
	moveDownSMenuKeyboard->SetButtonPressType(dae::ButtonPress::PressedDown);
	dae::InputManager::GetInstance().AddCommand(SDLK_s, std::move(moveDownSMenuKeyboard));

	auto selectEnterKeyboard = std::make_unique<SelectMenuCommand>();
	selectEnterKeyboard->SetActor(m_MenuComponentGO);
	selectEnterKeyboard->SetButtonPressType(dae::ButtonPress::PressedDown);
	dae::InputManager::GetInstance().AddCommand(SDLK_RETURN, std::move(selectEnterKeyboard));

	auto moveUpArrowMenuKeyboard = std::make_unique<MoveUpMenuCommand>();
	moveUpArrowMenuKeyboard->SetActor(m_MenuComponentGO);
	moveUpArrowMenuKeyboard->SetButtonPressType(dae::ButtonPress::PressedDown);
	dae::InputManager::GetInstance().AddCommand(SDLK_UP, std::move(moveUpArrowMenuKeyboard));

	auto moveDownArrowMenuKeyboard = std::make_unique<MoveDownMenuCommand>();
	moveDownArrowMenuKeyboard->SetActor(m_MenuComponentGO);
	moveDownArrowMenuKeyboard->SetButtonPressType(dae::ButtonPress::PressedDown);
	dae::InputManager::GetInstance().AddCommand(SDLK_DOWN, std::move(moveDownArrowMenuKeyboard));

	
	

	auto selectAController = std::make_unique<SelectMenuCommand>();
	selectAController->SetActor(m_MenuComponentGO);
	selectAController->SetButtonPressType(dae::ButtonPress::PressedDown);
	std::pair<unsigned, dae::ControllerButton> controllerKey(0, dae::ControllerButton::ButtonA);
	dae::InputManager::GetInstance().AddCommand(controllerKey, std::move(selectAController));

	auto selectBController = std::make_unique<SelectMenuCommand>();
	selectBController->SetActor(m_MenuComponentGO);
	selectBController->SetButtonPressType(dae::ButtonPress::PressedDown);
	controllerKey.second = dae::ControllerButton::ButtonB;
	dae::InputManager::GetInstance().AddCommand(controllerKey, std::move(selectBController));

	auto moveUpMenuController = std::make_unique<MoveUpMenuCommand>();
	moveUpMenuController->SetActor(m_MenuComponentGO);
	moveUpMenuController->SetButtonPressType(dae::ButtonPress::PressedDown);
	controllerKey.second = dae::ControllerButton::DPadUp;
	dae::InputManager::GetInstance().AddCommand(controllerKey, std::move(moveUpMenuController));

	auto moveDownMenuController = std::make_unique<MoveDownMenuCommand>();
	moveDownMenuController->SetActor(m_MenuComponentGO);
	moveDownMenuController->SetButtonPressType(dae::ButtonPress::PressedDown);
	controllerKey.second = dae::ControllerButton::DPadDown;
	dae::InputManager::GetInstance().AddCommand(controllerKey, std::move(moveDownMenuController));
}

void StartScreenInput::Update(const float)
{
}