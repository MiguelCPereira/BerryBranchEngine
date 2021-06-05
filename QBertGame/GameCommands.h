#pragma once
#include "Coily.h"
#include "Command.h"
#include "QBert.h"
#include "StartScreen.h"
#include "InstructionsScreen.h"
#include "VictoryDeathScreen.h"

// Menu Commands
class SelectMenuCommand final : public dae::Command
{
public:
	void Execute() override { GetActor()->GetComponent<StartScreen>()->StartGame(); }
};

class GoBackMenuCommand final : public dae::Command
{
public:
	void Execute() override { GetActor()->GetComponent<VictoryDeathScreen>()->GoBack(); }
};

class MoveUpMenuCommand final : public dae::Command
{
public:
	void Execute() override { GetActor()->GetComponent<StartScreen>()->ChangeSelection(true); }
};

class MoveDownMenuCommand final : public dae::Command
{
public:
	void Execute() override { GetActor()->GetComponent<StartScreen>()->ChangeSelection(false); }
};

class SkipInstructionsCommand final : public dae::Command
{
public:
	void Execute() override { GetActor()->GetComponent<InstructionsScreen>()->ChangeScene(); }
};




// QBert Commands
class QBertMoveUpCommand final : public dae::Command
{
public:
	void Execute() override { GetActor()->GetComponent<QBert>()->MoveUpRight(); }
};

class QBertMoveDownCommand final : public dae::Command
{
public:
	void Execute() override { GetActor()->GetComponent<QBert>()->MoveDownLeft(); }
};

class QBertMoveLeftCommand final : public dae::Command
{
public:
	void Execute() override { GetActor()->GetComponent<QBert>()->MoveUpLeft(); }
};

class QBertMoveRightCommand final : public dae::Command
{
public:
	void Execute() override { GetActor()->GetComponent<QBert>()->MoveDownRight(); }
};

class QBertPauseGameCommand final : public dae::Command
{
public:
	void Execute() override { GetActor()->GetComponent<QBert>()->PauseGame(); }
};

class QBertBackToMenuCommand final : public dae::Command
{
public:
	void Execute() override { GetActor()->GetComponent<QBert>()->BackToMenu(); }
};




// Coily Commands
class CoilyMoveUpCommand final : public dae::Command
{
public:
	void Execute() override { GetActor()->GetComponent<Coily>()->MoveUpRightPlayer(); }
};

class CoilyMoveDownCommand final : public dae::Command
{
public:
	void Execute() override { GetActor()->GetComponent<Coily>()->MoveDownLeftPlayer(); }
};

class CoilyMoveLeftCommand final : public dae::Command
{
public:
	void Execute() override { GetActor()->GetComponent<Coily>()->MoveUpLeftPlayer(); }
};

class CoilyMoveRightCommand final : public dae::Command
{
public:
	void Execute() override { GetActor()->GetComponent<Coily>()->MoveDownRightPlayer(); }
};

class CoilyPauseGameCommand final : public dae::Command
{
public:
	void Execute() override { GetActor()->GetComponent<Coily>()->PauseGame(); }
};

class CoilyBackToMenuCommand final : public dae::Command
{
public:
	void Execute() override { GetActor()->GetComponent<Coily>()->BackToMenu(); }
};