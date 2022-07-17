#include "MiniginPCH.h"
#include "InputManager.h"
#include <algorithm>


bool dae::InputManager::ProcessInput()
{
	ZeroMemory(&m_CurrentControllerState, sizeof(XINPUT_STATE));
	XInputGetState(m_ControllerNum, &m_CurrentControllerState);

	for (const auto button : AllButtons)
		ExecuteButton(button);

	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			return false;
		if (e.type == SDL_KEYDOWN)
			ExecuteKey(e.key.keysym.sym, false);
		if (e.type == SDL_KEYUP)
			ExecuteKey(e.key.keysym.sym, true);
		if (e.type == SDL_MOUSEBUTTONDOWN)
			ExecuteKey(e.key.keysym.sym, false);
		if (e.type == SDL_MOUSEBUTTONUP)
			ExecuteKey(e.key.keysym.sym, true);
	}
	
	return true;
}

bool dae::InputManager::IsPressed(ControllerButton button) const
{
	const int xInputButton = static_cast<int>(button);
	return m_CurrentControllerState.Gamepad.wButtons & xInputButton;
}

void dae::InputManager::ExecuteButton(ControllerButton button) const
{
	auto itr = m_ControllerCommands.find(ControllerKey(m_ControllerNum, button));
	
	if (itr != m_ControllerCommands.end())
	{
		if (IsPressed(button))
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
}

void dae::InputManager::ExecuteKey(SDL_Keycode key, bool keyUp) const
{
	auto itr = m_KeyboardCommands.find(key);

	if (itr != m_KeyboardCommands.end())
	{
		if (keyUp == false)
		{
			if (itr->second->GetPressType() == ButtonPress::PressedDown && itr->second->GetCommandExecuted() == false)
			{
				itr->second->SetCommandExecuted(true);
				itr->second->Execute();
			}
			else if (itr->second->GetPressType() == ButtonPress::PressedAndReleased && itr->second->GetCommandExecuted() == false)
			{
				itr->second->SetCommandExecuted(true);
				itr->second->Execute();
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
					itr->second->SetCommandExecuted(false);
					itr->second->Execute();
				}
			}
			else
			{
				if (itr->second->GetCommandExecuted() == true)
				{
					itr->second->SetCommandExecuted(false);
					
					if (itr->second->GetPressType() == ButtonPress::PressedAndReleased)
					{
						itr->second->Execute();
					}
				}
			}
		}
	}
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

void dae::InputManager::ClearAllCommands()
{
	m_ControllerCommands.clear();
	m_KeyboardCommands.clear();
}

void dae::InputManager::RemoveCommand(ControllerKey button)
{
	const auto removedCommandIt = m_ControllerCommands.find(button);
	
	if (removedCommandIt != m_ControllerCommands.end())
		m_ControllerCommands.erase(removedCommandIt);
	else
		std::cout << "Trying to remove a command that wasn't assigned in the first place\n";
}

void dae::InputManager::RemoveCommand(SDL_Keycode key)
{
	const auto removedCommandIt = m_KeyboardCommands.find(key);

	if (removedCommandIt != m_KeyboardCommands.end())
		m_KeyboardCommands.erase(removedCommandIt);
	else
		std::cout << "Trying to remove a command that wasn't assigned in the first place\n";
}

