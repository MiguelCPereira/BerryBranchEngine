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

	// Keyboard P1
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


	// Keyboard P2
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

	
	
	// Controller P1
	auto p1SelectAController = std::make_unique<SelectMenuCommand>();
	p1SelectAController->SetActor(m_MenuComponentGO);
	p1SelectAController->SetButtonPressType(dae::ButtonPress::PressedDown);
	std::pair<unsigned, dae::ControllerButton> controllerKey(0, dae::ControllerButton::ButtonA);
	dae::InputManager::GetInstance().AddCommand(controllerKey, std::move(p1SelectAController));

	auto p1SelectBController = std::make_unique<SelectMenuCommand>();
	p1SelectBController->SetActor(m_MenuComponentGO);
	p1SelectBController->SetButtonPressType(dae::ButtonPress::PressedDown);
	controllerKey.second = dae::ControllerButton::ButtonB;
	dae::InputManager::GetInstance().AddCommand(controllerKey, std::move(p1SelectBController));

	auto p1SelectStartController = std::make_unique<SelectMenuCommand>();
	p1SelectStartController->SetActor(m_MenuComponentGO);
	p1SelectStartController->SetButtonPressType(dae::ButtonPress::PressedDown);
	controllerKey.second = dae::ControllerButton::Start;
	dae::InputManager::GetInstance().AddCommand(controllerKey, std::move(p1SelectStartController));

	auto p1MoveUpMenuController = std::make_unique<MoveUpMenuCommand>();
	p1MoveUpMenuController->SetActor(m_MenuComponentGO);
	p1MoveUpMenuController->SetButtonPressType(dae::ButtonPress::PressedDown);
	controllerKey.second = dae::ControllerButton::DPadUp;
	dae::InputManager::GetInstance().AddCommand(controllerKey, std::move(p1MoveUpMenuController));

	auto p1MoveDownMenuController = std::make_unique<MoveDownMenuCommand>();
	p1MoveDownMenuController->SetActor(m_MenuComponentGO);
	p1MoveDownMenuController->SetButtonPressType(dae::ButtonPress::PressedDown);
	controllerKey.second = dae::ControllerButton::DPadDown;
	dae::InputManager::GetInstance().AddCommand(controllerKey, std::move(p1MoveDownMenuController));


	// Controller P2
	auto p2SelectAController = std::make_unique<SelectMenuCommand>();
	p2SelectAController->SetActor(m_MenuComponentGO);
	p2SelectAController->SetButtonPressType(dae::ButtonPress::PressedDown);
	controllerKey.first = 1;
	controllerKey.second = dae::ControllerButton::ButtonA;
	dae::InputManager::GetInstance().AddCommand(controllerKey, std::move(p2SelectAController));

	auto p2SelectBController = std::make_unique<SelectMenuCommand>();
	p2SelectBController->SetActor(m_MenuComponentGO);
	p2SelectBController->SetButtonPressType(dae::ButtonPress::PressedDown);
	controllerKey.second = dae::ControllerButton::ButtonB;
	dae::InputManager::GetInstance().AddCommand(controllerKey, std::move(p2SelectBController));

	auto p2SelectStartController = std::make_unique<SelectMenuCommand>();
	p2SelectStartController->SetActor(m_MenuComponentGO);
	p2SelectStartController->SetButtonPressType(dae::ButtonPress::PressedDown);
	controllerKey.second = dae::ControllerButton::Start;
	dae::InputManager::GetInstance().AddCommand(controllerKey, std::move(p2SelectStartController));

	auto p2MoveUpMenuController = std::make_unique<MoveUpMenuCommand>();
	p2MoveUpMenuController->SetActor(m_MenuComponentGO);
	p2MoveUpMenuController->SetButtonPressType(dae::ButtonPress::PressedDown);
	controllerKey.second = dae::ControllerButton::DPadUp;
	dae::InputManager::GetInstance().AddCommand(controllerKey, std::move(p2MoveUpMenuController));

	auto p2MoveDownMenuController = std::make_unique<MoveDownMenuCommand>();
	p2MoveDownMenuController->SetActor(m_MenuComponentGO);
	p2MoveDownMenuController->SetButtonPressType(dae::ButtonPress::PressedDown);
	controllerKey.second = dae::ControllerButton::DPadDown;
	dae::InputManager::GetInstance().AddCommand(controllerKey, std::move(p2MoveDownMenuController));
}

void StartScreenInput::Update(const float)
{
}