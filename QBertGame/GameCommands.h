#pragma once
#include "Command.h"
#include "QBert.h"

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

