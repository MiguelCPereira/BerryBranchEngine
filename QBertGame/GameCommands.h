#pragma once
#include "Command.h"
#include "QBert.h"
#include "StartScreen.h"
#include "VictoryDeathScreen.h"

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

