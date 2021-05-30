#include "PlayerTwoCoilyInput.h"
#include "GameCommands.h"
#include "InputManager.h"

PlayerTwoCoilyInput::PlayerTwoCoilyInput(const std::shared_ptr<dae::GameObject>& coilyGO)
	: m_CoilyGO(coilyGO)
{
}

void PlayerTwoCoilyInput::Initialize()
{
	auto moveUpKeyboard = std::make_unique<CoilyMoveUpCommand>();
	moveUpKeyboard->SetActor(m_CoilyGO);
	moveUpKeyboard->SetButtonPressType(dae::ButtonPress::PressedDown);
	dae::InputManager::GetInstance().AddCommand(SDLK_UP, std::move(moveUpKeyboard));

	auto moveDownKeyboard = std::make_unique<CoilyMoveDownCommand>();
	moveDownKeyboard->SetActor(m_CoilyGO);
	moveDownKeyboard->SetButtonPressType(dae::ButtonPress::PressedDown);
	dae::InputManager::GetInstance().AddCommand(SDLK_DOWN, std::move(moveDownKeyboard));

	auto moveLeftKeyboard = std::make_unique<CoilyMoveLeftCommand>();
	moveLeftKeyboard->SetActor(m_CoilyGO);
	moveLeftKeyboard->SetButtonPressType(dae::ButtonPress::PressedDown);
	dae::InputManager::GetInstance().AddCommand(SDLK_LEFT, std::move(moveLeftKeyboard));

	auto moveRightKeyboard = std::make_unique<CoilyMoveRightCommand>();
	moveRightKeyboard->SetActor(m_CoilyGO);
	moveRightKeyboard->SetButtonPressType(dae::ButtonPress::PressedDown);
	dae::InputManager::GetInstance().AddCommand(SDLK_RIGHT, std::move(moveRightKeyboard));



	auto moveUpController = std::make_unique<CoilyMoveUpCommand>();
	moveUpController->SetActor(m_CoilyGO);
	moveUpController->SetButtonPressType(dae::ButtonPress::PressedDown);
	std::pair<unsigned, dae::ControllerButton> controllerKey(1, dae::ControllerButton::DPadUp);
	dae::InputManager::GetInstance().AddCommand(controllerKey, std::move(moveUpController));

	auto moveDownController = std::make_unique<CoilyMoveDownCommand>();
	moveDownController->SetActor(m_CoilyGO);
	moveDownController->SetButtonPressType(dae::ButtonPress::PressedDown);
	controllerKey.second = dae::ControllerButton::DPadDown;
	dae::InputManager::GetInstance().AddCommand(controllerKey, std::move(moveDownController));

	auto moveLeftController = std::make_unique<CoilyMoveLeftCommand>();
	moveLeftController->SetActor(m_CoilyGO);
	moveLeftController->SetButtonPressType(dae::ButtonPress::PressedDown);
	controllerKey.second = dae::ControllerButton::DPadLeft;
	dae::InputManager::GetInstance().AddCommand(controllerKey, std::move(moveLeftController));

	auto moveRightController = std::make_unique<CoilyMoveRightCommand>();
	moveRightController->SetActor(m_CoilyGO);
	moveRightController->SetButtonPressType(dae::ButtonPress::PressedDown);
	controllerKey.second = dae::ControllerButton::DPadRight;
	dae::InputManager::GetInstance().AddCommand(controllerKey, std::move(moveRightController));
}

void PlayerTwoCoilyInput::Update(const float)
{
}

