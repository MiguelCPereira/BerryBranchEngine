#pragma once
#include <iostream>
#include <memory>
#include "GameObject.h"
#include "QBertComponent.h"
#include "SoundSystem.h"

namespace dae
{
	enum class ButtonPress
	{
		PressedDown,
		Released,
		PressedAndReleased,
		WhilePressed
	};


	class Command
	{
	protected:
		std::shared_ptr<GameObject> GetActor() const { return m_Actor; }
	public:
		Command() = default;
		virtual ~Command() = default;
		virtual void Execute() = 0;
		void SetActor(std::shared_ptr<GameObject> actor) { m_Actor = actor; }
		void SetButtonPressType(ButtonPress pressType) { m_PressType = pressType; }
		void SetCommandExecuted(bool executed) { m_CommandExecuted = executed; }
		ButtonPress GetPressType() const { return m_PressType; }
		bool GetCommandExecuted() const { return m_CommandExecuted; }

		Command(const Command& other) = delete;
		Command(Command&& other) = delete;
		Command& operator=(const Command& other) = delete;
		Command& operator=(Command&& other) = delete;

	private:
		ButtonPress m_PressType;
		bool m_CommandExecuted; // In case we only want to execute one each button press
		std::shared_ptr<dae::GameObject> m_Actor;
	};



	
	class DieCommand final : public Command
	{
	public:
		void Execute() override { GetActor()->GetComponent<QBertComponent>()->Die(); }
	};

	class ColorChangeCommand final : public Command
	{
	public:
		void Execute() override { GetActor()->GetComponent<QBertComponent>()->ChangeColor(); }
	};

	class TileChangeCommand final : public Command
	{
	public:
		void Execute() override { GetActor()->GetComponent<QBertComponent>()->ChangeTile(); }
	};

	class PlaySoundCommand final : public Command
	{
	public:
		PlaySoundCommand(SoundSystem* soundSystem) : m_SoundSystem{ soundSystem } {}
		void Execute() override { m_SoundSystem->Play("../Data/Sounds/Demo Sound.wav", 0.5f); }
	private:
		SoundSystem* m_SoundSystem;
	};
	
	
	class FireCommand final : public Command
	{
	public:
		void Execute() override { std::cout << "Firing\n"; }
	};

	class DuckCommand final : public Command
	{
	public:
		void Execute() override { std::cout << "Ducking\n"; }
	};

	class JumpCommand final : public Command
	{
	public:
		void Execute() override { std::cout << "Jumping\n"; }
	};
}
