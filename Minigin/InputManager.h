#pragma once
#include <windows.h>
#include <XInput.h>
#pragma comment(lib, "XInput.lib")
#include <SDL.h>
#include <map>
#include <vector>
#include "Command.h"
#include "Singleton.h"

namespace dae
{
	enum class ControllerButton
	{
		ButtonA = 0x1000,
		ButtonB = 0x2000,
		ButtonX = 0x4000,
		ButtonY = 0x8000,
		DPadUp = 0x00000001,
		DPadDown = 0x00000002,
		DPadLeft = 0x00000004,
		DPadRight = 0x00000008,
		Start = 0x00000010,
		Select = 0x00000020,
		LeftThumb = 0x00000040,
		RightThumb = 0x00000080,
		LeftShoulder = 0x0100,
		RightShoulder = 0x0200
	};

	using ControllerKey = std::pair <unsigned, ControllerButton>;
	using ControllerCommandsMap = std::map<ControllerKey, std::unique_ptr<Command>>;
	using KeyboardCommandsMap = std::map<SDL_Keycode, std::unique_ptr<Command>>;
	
	class InputManager final : public Singleton<InputManager>
	{
	public:
		void AddCommand(ControllerKey button, std::unique_ptr<Command> command);
		void AddCommand(SDL_Keycode key, std::unique_ptr<Command> command);
		bool ProcessInput();
		bool IsPressed(ControllerButton button) const;
		bool IsPressed(SDL_Keycode key, bool keyUp) const;

	private:
		XINPUT_STATE m_CurrentControllerState{};
		int m_ControllerNum = 0;
		ControllerCommandsMap m_ControllerCommands{};
		KeyboardCommandsMap m_KeyboardCommands{};
	};

}
