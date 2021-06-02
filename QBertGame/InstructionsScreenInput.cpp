#include "InstructionsScreenInput.h"
#include "GameCommands.h"
#include "InputManager.h"

InstructionsScreenInput::InstructionsScreenInput(const std::shared_ptr<dae::GameObject>& instructionsComponentGO)
	: m_InstructionsComponentGO(instructionsComponentGO)
{
}

void InstructionsScreenInput::Initialize()
{
	dae::InputManager::GetInstance().ClearAllCommands();

	auto goBackKeyboard = std::make_unique<SkipInstructionsCommand>();
	goBackKeyboard->SetActor(m_InstructionsComponentGO);
	goBackKeyboard->SetButtonPressType(dae::ButtonPress::PressedDown);
	dae::InputManager::GetInstance().AddCommand(SDLK_RETURN, std::move(goBackKeyboard));


	auto goBackController1 = std::make_unique<SkipInstructionsCommand>();
	goBackController1->SetActor(m_InstructionsComponentGO);
	goBackController1->SetButtonPressType(dae::ButtonPress::PressedDown);
	std::pair<unsigned, dae::ControllerButton> controllerKey(0, dae::ControllerButton::Start);
	dae::InputManager::GetInstance().AddCommand(controllerKey, std::move(goBackController1));


	auto goBackController2 = std::make_unique<SkipInstructionsCommand>();
	goBackController2->SetActor(m_InstructionsComponentGO);
	goBackController2->SetButtonPressType(dae::ButtonPress::PressedDown);
	controllerKey.first = 1;
	dae::InputManager::GetInstance().AddCommand(controllerKey, std::move(goBackController2));
}

void InstructionsScreenInput::Update(const float)
{
}
