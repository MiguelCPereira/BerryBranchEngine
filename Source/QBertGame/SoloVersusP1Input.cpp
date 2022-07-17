#include "SoloVersusP1Input.h"
#include "GameCommands.h"
#include "InputManager.h"

SoloVersusP1Input::SoloVersusP1Input(const std::shared_ptr<dae::GameObject>& qBertGO)
	: m_QBertGO(qBertGO)
{
}

void SoloVersusP1Input::Initialize()
{
	dae::InputManager::GetInstance().ClearAllCommands();

	// Keyboard
	
	auto moveUpKeyboard = std::make_unique<QBertMoveUpCommand>();
	moveUpKeyboard->SetActor(m_QBertGO);
	moveUpKeyboard->SetButtonPressType(dae::ButtonPress::PressedDown);
	dae::InputManager::GetInstance().AddCommand(SDLK_w, std::move(moveUpKeyboard));

	auto moveDownKeyboard = std::make_unique<QBertMoveDownCommand>();
	moveDownKeyboard->SetActor(m_QBertGO);
	moveDownKeyboard->SetButtonPressType(dae::ButtonPress::PressedDown);
	dae::InputManager::GetInstance().AddCommand(SDLK_s, std::move(moveDownKeyboard));

	auto moveLeftKeyboard = std::make_unique<QBertMoveLeftCommand>();
	moveLeftKeyboard->SetActor(m_QBertGO);
	moveLeftKeyboard->SetButtonPressType(dae::ButtonPress::PressedDown);
	dae::InputManager::GetInstance().AddCommand(SDLK_a, std::move(moveLeftKeyboard));

	auto moveRightKeyboard = std::make_unique<QBertMoveRightCommand>();
	moveRightKeyboard->SetActor(m_QBertGO);
	moveRightKeyboard->SetButtonPressType(dae::ButtonPress::PressedDown);
	dae::InputManager::GetInstance().AddCommand(SDLK_d, std::move(moveRightKeyboard));

	auto pauseKeyboard = std::make_unique<QBertPauseGameCommand>();
	pauseKeyboard->SetActor(m_QBertGO);
	pauseKeyboard->SetButtonPressType(dae::ButtonPress::PressedDown);
	dae::InputManager::GetInstance().AddCommand(SDLK_p, std::move(pauseKeyboard));

	auto backToMenuKeyboard = std::make_unique<QBertBackToMenuCommand>();
	backToMenuKeyboard->SetActor(m_QBertGO);
	backToMenuKeyboard->SetButtonPressType(dae::ButtonPress::PressedDown);
	dae::InputManager::GetInstance().AddCommand(SDLK_ESCAPE, std::move(backToMenuKeyboard));



	// Controller
	
	auto moveUpController = std::make_unique<QBertMoveUpCommand>();
	moveUpController->SetActor(m_QBertGO);
	moveUpController->SetButtonPressType(dae::ButtonPress::PressedDown);
	std::pair<unsigned, dae::ControllerButton> controllerKey(0, dae::ControllerButton::DPadUp);
	dae::InputManager::GetInstance().AddCommand(controllerKey, std::move(moveUpController));

	auto moveDownController = std::make_unique<QBertMoveDownCommand>();
	moveDownController->SetActor(m_QBertGO);
	moveDownController->SetButtonPressType(dae::ButtonPress::PressedDown);
	controllerKey.second = dae::ControllerButton::DPadDown;
	dae::InputManager::GetInstance().AddCommand(controllerKey, std::move(moveDownController));

	auto moveLeftController = std::make_unique<QBertMoveLeftCommand>();
	moveLeftController->SetActor(m_QBertGO);
	moveLeftController->SetButtonPressType(dae::ButtonPress::PressedDown);
	controllerKey.second = dae::ControllerButton::DPadLeft;
	dae::InputManager::GetInstance().AddCommand(controllerKey, std::move(moveLeftController));

	auto moveRightController = std::make_unique<QBertMoveRightCommand>();
	moveRightController->SetActor(m_QBertGO);
	moveRightController->SetButtonPressType(dae::ButtonPress::PressedDown);
	controllerKey.second = dae::ControllerButton::DPadRight;
	dae::InputManager::GetInstance().AddCommand(controllerKey, std::move(moveRightController));

	auto pauseController = std::make_unique<QBertPauseGameCommand>();
	pauseController->SetActor(m_QBertGO);
	pauseController->SetButtonPressType(dae::ButtonPress::PressedDown);
	controllerKey.second = dae::ControllerButton::Start;
	dae::InputManager::GetInstance().AddCommand(controllerKey, std::move(pauseController));

	auto backToMenuController = std::make_unique<QBertBackToMenuCommand>();
	backToMenuController->SetActor(m_QBertGO);
	backToMenuController->SetButtonPressType(dae::ButtonPress::PressedDown);
	controllerKey.second = dae::ControllerButton::ButtonY;
	dae::InputManager::GetInstance().AddCommand(controllerKey, std::move(backToMenuController));
}

void SoloVersusP1Input::Update(const float)
{
}


