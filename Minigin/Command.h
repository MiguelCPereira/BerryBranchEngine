#pragma once
#include <iostream>
#include <memory>
#include "GameObject.h"
//#include "LifeComponent.h"

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
	std::shared_ptr<dae::GameObject> GetActor() const { return m_Actor; }
public:
	Command() = default;
	Command(std::shared_ptr<dae::GameObject> actor)
		: m_PressType(ButtonPress::PressedDown),
		m_CommandExecuted(false),
		m_Actor(actor)
	{}
	virtual ~Command() = default;
	virtual void Execute() = 0;
	void SetButtonPressType(ButtonPress pressType) { m_PressType = pressType; }
	void SetCommandExecuted(bool executed) { m_CommandExecuted = executed; }
	ButtonPress GetPressType() const { return m_PressType; }
	bool GetCommandExecuted() const { return m_CommandExecuted; }
	//virtual void Undo() = 0;

	Command(const Command& other) = delete;
	Command(Command&& other) = delete;
	Command& operator=(const Command& other) = delete;
	Command& operator=(Command&& other) = delete;

private:
	ButtonPress m_PressType;
	bool m_CommandExecuted; // In case we only want to execute one each button press
	std::shared_ptr<dae::GameObject> m_Actor;
};

class FireCommand : public Command
{
public:
	void Execute() override { /*GetActor()->Fire();*/ std::cout << "Firing\n"; }
};

class DuckCommand : public Command
{
public:
	void Execute() override { /*GetActor()->Duck();*/std::cout << "Ducking\n"; }
};

class JumpCommand : public Command
{
public:
	void Execute() override { /*GetActor()->Jump();*/std::cout << "Jumping\n"; }
};

class FartCommand : public Command
{
public:
	void Execute() override { /*GetActor()->Fart();*/std::cout << "Farting\n"; }
};

class DieCommand : public Command
{
public:
	void Execute() override { /*GetActor()->getComponent<dae::QBertLifeComponent>()->GetDamaged(3);*/ std::cout << "Player Died\n"; }
};
