#include "CoopAllInput.h"
#include "GameCommands.h"
#include "InputManager.h"

CoopAllInput::CoopAllInput(const std::shared_ptr<dae::GameObject>& qBert1GO, const std::shared_ptr<dae::GameObject>& qBert2GO)
	: m_QBert1GO(qBert1GO)
	, m_QBert2GO(qBert2GO)
{
}

void CoopAllInput::Initialize()
{
	dae::InputManager::GetInstance().ClearAllCommands();


	// PLAYER 01

	auto p1MoveUpKeyboard = std::make_unique<QBertMoveUpCommand>();
	p1MoveUpKeyboard->SetActor(m_QBert1GO);
	p1MoveUpKeyboard->SetButtonPressType(dae::ButtonPress::PressedDown);
	dae::InputManager::GetInstance().AddCommand(SDLK_w, std::move(p1MoveUpKeyboard));

	auto p1MoveDownKeyboard = std::make_unique<QBertMoveDownCommand>();
	p1MoveDownKeyboard->SetActor(m_QBert1GO);
	p1MoveDownKeyboard->SetButtonPressType(dae::ButtonPress::PressedDown);
	dae::InputManager::GetInstance().AddCommand(SDLK_s, std::move(p1MoveDownKeyboard));

	auto p1MoveLeftKeyboard = std::make_unique<QBertMoveLeftCommand>();
	p1MoveLeftKeyboard->SetActor(m_QBert1GO);
	p1MoveLeftKeyboard->SetButtonPressType(dae::ButtonPress::PressedDown);
	dae::InputManager::GetInstance().AddCommand(SDLK_a, std::move(p1MoveLeftKeyboard));

	auto p1MoveRightKeyboard = std::make_unique<QBertMoveRightCommand>();
	p1MoveRightKeyboard->SetActor(m_QBert1GO);
	p1MoveRightKeyboard->SetButtonPressType(dae::ButtonPress::PressedDown);
	dae::InputManager::GetInstance().AddCommand(SDLK_d, std::move(p1MoveRightKeyboard));



	auto p1MoveUpController = std::make_unique<QBertMoveUpCommand>();
	p1MoveUpController->SetActor(m_QBert1GO);
	p1MoveUpController->SetButtonPressType(dae::ButtonPress::PressedDown);
	std::pair<unsigned, dae::ControllerButton> controllerKey(0, dae::ControllerButton::DPadUp);
	dae::InputManager::GetInstance().AddCommand(controllerKey, std::move(p1MoveUpController));

	auto p1MoveDownController = std::make_unique<QBertMoveDownCommand>();
	p1MoveDownController->SetActor(m_QBert1GO);
	p1MoveDownController->SetButtonPressType(dae::ButtonPress::PressedDown);
	controllerKey.second = dae::ControllerButton::DPadDown;
	dae::InputManager::GetInstance().AddCommand(controllerKey, std::move(p1MoveDownController));

	auto p1MoveLeftController = std::make_unique<QBertMoveLeftCommand>();
	p1MoveLeftController->SetActor(m_QBert1GO);
	p1MoveLeftController->SetButtonPressType(dae::ButtonPress::PressedDown);
	controllerKey.second = dae::ControllerButton::DPadLeft;
	dae::InputManager::GetInstance().AddCommand(controllerKey, std::move(p1MoveLeftController));

	auto p1MoveRightController = std::make_unique<QBertMoveRightCommand>();
	p1MoveRightController->SetActor(m_QBert1GO);
	p1MoveRightController->SetButtonPressType(dae::ButtonPress::PressedDown);
	controllerKey.second = dae::ControllerButton::DPadRight;
	dae::InputManager::GetInstance().AddCommand(controllerKey, std::move(p1MoveRightController));



	// PLAYER 02

	auto p2MoveUpKeyboard = std::make_unique<QBertMoveUpCommand>();
	p2MoveUpKeyboard->SetActor(m_QBert2GO);
	p2MoveUpKeyboard->SetButtonPressType(dae::ButtonPress::PressedDown);
	dae::InputManager::GetInstance().AddCommand(SDLK_UP, std::move(p2MoveUpKeyboard));

	auto p2MoveDownKeyboard = std::make_unique<QBertMoveDownCommand>();
	p2MoveDownKeyboard->SetActor(m_QBert2GO);
	p2MoveDownKeyboard->SetButtonPressType(dae::ButtonPress::PressedDown);
	dae::InputManager::GetInstance().AddCommand(SDLK_DOWN, std::move(p2MoveDownKeyboard));

	auto p2MoveLeftKeyboard = std::make_unique<QBertMoveLeftCommand>();
	p2MoveLeftKeyboard->SetActor(m_QBert2GO);
	p2MoveLeftKeyboard->SetButtonPressType(dae::ButtonPress::PressedDown);
	dae::InputManager::GetInstance().AddCommand(SDLK_LEFT, std::move(p2MoveLeftKeyboard));

	auto p2MoveRightKeyboard = std::make_unique<QBertMoveRightCommand>();
	p2MoveRightKeyboard->SetActor(m_QBert2GO);
	p2MoveRightKeyboard->SetButtonPressType(dae::ButtonPress::PressedDown);
	dae::InputManager::GetInstance().AddCommand(SDLK_RIGHT, std::move(p2MoveRightKeyboard));



	auto p2MoveUpController = std::make_unique<QBertMoveUpCommand>();
	p2MoveUpController->SetActor(m_QBert2GO);
	p2MoveUpController->SetButtonPressType(dae::ButtonPress::PressedDown);
	controllerKey.first = 1;
	controllerKey.second = dae::ControllerButton::DPadUp;
	dae::InputManager::GetInstance().AddCommand(controllerKey, std::move(p2MoveUpController));

	auto p2MoveDownController = std::make_unique<QBertMoveDownCommand>();
	p2MoveDownController->SetActor(m_QBert2GO);
	p2MoveDownController->SetButtonPressType(dae::ButtonPress::PressedDown);
	controllerKey.second = dae::ControllerButton::DPadDown;
	dae::InputManager::GetInstance().AddCommand(controllerKey, std::move(p2MoveDownController));

	auto p2MoveLeftController = std::make_unique<QBertMoveLeftCommand>();
	p2MoveLeftController->SetActor(m_QBert2GO);
	p2MoveLeftController->SetButtonPressType(dae::ButtonPress::PressedDown);
	controllerKey.second = dae::ControllerButton::DPadLeft;
	dae::InputManager::GetInstance().AddCommand(controllerKey, std::move(p2MoveLeftController));

	auto p2MoveRightController = std::make_unique<QBertMoveRightCommand>();
	p2MoveRightController->SetActor(m_QBert2GO);
	p2MoveRightController->SetButtonPressType(dae::ButtonPress::PressedDown);
	controllerKey.second = dae::ControllerButton::DPadRight;
	dae::InputManager::GetInstance().AddCommand(controllerKey, std::move(p2MoveRightController));
}

void CoopAllInput::Update(const float)
{
}