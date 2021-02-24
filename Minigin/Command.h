#pragma once
#include <iostream>

enum class ButtonPress
{
	PressedDown,
	Released,
	PressedAndReleased,
	WhilePressed
};


class Command
{
	//protected:
		//GameActor* GetActor() const { return m_Actor; }
public:
	Command(/*GameActor* actor*/)/* : m_Actor(actor)*/ = default;
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
	bool m_CommandExecuted; // In case we only want to execute one each buttonpress
	//GameActor* m_Actor;
};

class FireCommand : public Command
{
public:
	void Execute() override { /*m_Actor->Fire();*/ std::cout << "Firing\n"; }
};

class DuckCommand : public Command
{
public:
	void Execute() override { /*m_Actor->Duck();*/std::cout << "Ducking\n"; }
};

class JumpCommand : public Command
{
public:
	void Execute() override { /*m_Actor->Jump();*/std::cout << "Jumping\n"; }
};

class FartCommand : public Command
{
public:
	void Execute() override { /*m_Actor->Fart();*/std::cout << "Farting\n"; }
};
