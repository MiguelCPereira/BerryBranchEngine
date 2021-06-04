#include "P2CoilyInput.h"
#include "GameCommands.h"
#include "InputManager.h"
#include "Coily.h"

P2CoilyInput::P2CoilyInput(const std::shared_ptr<dae::GameObject>& coilyGO)
	: m_CoilyGO(coilyGO)
	, m_CoilyComp()
	, m_Deactivated(false)
{
}

P2CoilyInput::~P2CoilyInput()
{
	if (m_CoilyComp != nullptr)
		m_CoilyComp->GetSubject()->RemoveObserver(this);
}

void P2CoilyInput::Initialize()
{
	// Start Observing
	if (m_Deactivated == false && m_CoilyGO != nullptr)
	{
		m_CoilyComp = m_CoilyGO->GetComponent<Coily>();
		if (m_CoilyComp != nullptr)
			m_CoilyComp->GetSubject()->AddObserver(this);

	

		// Register Input
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
}

void P2CoilyInput::OnNotify(const dae::Event& event)
{
	switch (event)
	{
	case dae::Event::CoilyFell:
		ClearInput();
		if (m_CoilyComp != nullptr)
		{
			m_CoilyComp->GetSubject()->RemoveObserver(this);
			m_CoilyComp->Die();
			m_Deactivated = true;
		}

		break;

	case dae::Event::CoilyHitQBert:
		ClearInput();
		if (m_CoilyComp != nullptr)
		{
			m_CoilyComp->GetSubject()->RemoveObserver(this);
			m_Deactivated = true;
			// We don't kill Coily already, because they still need to be frozen and alive for a while,
			// as the damaged QBert curses (and after that, LevelSectionObserver will kill it along with
			// every other foe in the map)
		}

		break;
	}
}

void P2CoilyInput::Update(const float)
{
}

void P2CoilyInput::ClearInput() const
{
	dae::InputManager::GetInstance().RemoveCommand(SDLK_UP);
	dae::InputManager::GetInstance().RemoveCommand(SDLK_DOWN);
	dae::InputManager::GetInstance().RemoveCommand(SDLK_LEFT);
	dae::InputManager::GetInstance().RemoveCommand(SDLK_RIGHT);

	std::pair<unsigned, dae::ControllerButton> controllerKey(1, dae::ControllerButton::DPadUp);
	dae::InputManager::GetInstance().RemoveCommand(controllerKey);
	controllerKey.second = dae::ControllerButton::DPadDown;
	dae::InputManager::GetInstance().RemoveCommand(controllerKey);
	controllerKey.second = dae::ControllerButton::DPadLeft;
	dae::InputManager::GetInstance().RemoveCommand(controllerKey);
	controllerKey.second = dae::ControllerButton::DPadRight;
	dae::InputManager::GetInstance().RemoveCommand(controllerKey);
}

