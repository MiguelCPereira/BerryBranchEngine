#include "MiniginPCH.h"
#include "InputManager.h"


bool dae::InputManager::ProcessInput()
{
	ZeroMemory(&m_CurrentControllerState, sizeof(XINPUT_STATE));
	XInputGetState(m_ControllerNum, &m_CurrentControllerState);

	IsPressed(ControllerButton::ButtonA);
	IsPressed(ControllerButton::ButtonB);
	IsPressed(ControllerButton::ButtonY);
	IsPressed(ControllerButton::ButtonX);
	IsPressed(ControllerButton::DPadUp);
	IsPressed(ControllerButton::DPadDown);
	IsPressed(ControllerButton::DPadLeft);
	IsPressed(ControllerButton::DPadRight);
	IsPressed(ControllerButton::LeftThumb);
	IsPressed(ControllerButton::RightThumb);
	IsPressed(ControllerButton::LeftShoulder);
	IsPressed(ControllerButton::RightShoulder);
	IsPressed(ControllerButton::Start);
	IsPressed(ControllerButton::Select);

	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			return false;
		if (e.type == SDL_KEYDOWN)
			IsPressed(e.key.keysym.sym, false);
		if (e.type == SDL_KEYUP)
			IsPressed(e.key.keysym.sym, true);
		if (e.type == SDL_MOUSEBUTTONDOWN)
			IsPressed(e.key.keysym.sym, false);
		if (e.type == SDL_MOUSEBUTTONUP)
			IsPressed(e.key.keysym.sym, true);
		if (e.type == SDL_MOUSEMOTION) {
			// Process Mouse Movement
		}
	}
	
	return true;
}

bool dae::InputManager::IsPressed(ControllerButton button) const
{
	const int xInputButton = static_cast<int>(button);
	auto itr = m_ControllerCommands.find(ControllerKey(m_ControllerNum, button));

	if (m_CurrentControllerState.Gamepad.wButtons & xInputButton)
	{
		if (itr != m_ControllerCommands.end())
		{
			if (itr->second->GetPressType() == ButtonPress::PressedDown && itr->second->GetCommandExecuted() == false)
			{
				itr->second->Execute();
				itr->second->SetCommandExecuted(true);
			}
			else if (itr->second->GetPressType() == ButtonPress::PressedAndReleased && itr->second->GetCommandExecuted() == false)
			{
				itr->second->Execute();
				itr->second->SetCommandExecuted(true);
			}
			else if (itr->second->GetPressType() == ButtonPress::WhilePressed)
			{
				itr->second->Execute();
			}
			else if (itr->second->GetPressType() == ButtonPress::Released)
			{
				itr->second->SetCommandExecuted(true); // The "CommandExecuted" bool works inverted on Released, so even though the execution will only happen in the next if statement, we already switch the bool
			}
		}
		return true;
	}

	if (itr != m_ControllerCommands.end())
	{
		if (itr->second->GetPressType() == ButtonPress::Released)
		{
			if (itr->second->GetCommandExecuted() == true)
			{
				itr->second->Execute();
				itr->second->SetCommandExecuted(false);
			}
		}
		else
		{
			if (itr->second->GetCommandExecuted() == true)
			{
				if (itr->second->GetPressType() == ButtonPress::PressedAndReleased)
				{
					itr->second->Execute();
				}

				itr->second->SetCommandExecuted(false);
			}
		}
	}

	return false;
}

bool dae::InputManager::IsPressed(SDL_Keycode key, bool keyUp) const
{
	auto itr = m_KeyboardCommands.find(key);

	if (itr != m_KeyboardCommands.end())
	{
		if (keyUp == false)
		{
			if (itr->second->GetPressType() == ButtonPress::PressedDown && itr->second->GetCommandExecuted() == false)
			{
				itr->second->Execute();
				itr->second->SetCommandExecuted(true);
			}
			else if (itr->second->GetPressType() == ButtonPress::PressedAndReleased && itr->second->GetCommandExecuted() == false)
			{
				itr->second->Execute();
				itr->second->SetCommandExecuted(true);
			}
			else if (itr->second->GetPressType() == ButtonPress::WhilePressed)
			{
				itr->second->Execute();
			}
			else if (itr->second->GetPressType() == ButtonPress::Released)
			{
				itr->second->SetCommandExecuted(true); // The "CommandExecuted" bool works inverted on Released, so even though the execution will only happen in the next if statement, we already switch the bool
			}
		}
		else
		{
			if (itr->second->GetPressType() == ButtonPress::Released)
			{
				if (itr->second->GetCommandExecuted() == true)
				{
					itr->second->Execute();
					itr->second->SetCommandExecuted(false);
				}
			}
			else
			{
				if (itr->second->GetCommandExecuted() == true)
				{
					if (itr->second->GetPressType() == ButtonPress::PressedAndReleased)
					{
						itr->second->Execute();
					}

					itr->second->SetCommandExecuted(false);
				}
			}
		}
	}

	return false;
}

void dae::InputManager::AddCommand(ControllerKey button, std::unique_ptr<Command> command)
{
	if (m_ControllerCommands.find(button) != m_ControllerCommands.end())
		std::cout << "A command is already assigned to this button - it will be overwritten\n";

	m_ControllerCommands.insert_or_assign(button, std::move(command));
}

void dae::InputManager::AddCommand(SDL_Keycode key, std::unique_ptr<Command> command)
{
	if (m_KeyboardCommands.find(key) != m_KeyboardCommands.end())
		std::cout << "A command is already assigned to this key - it will be overwritten\n";

	m_KeyboardCommands.insert_or_assign(key, std::move(command));
}

