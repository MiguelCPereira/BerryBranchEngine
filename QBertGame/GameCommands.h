#pragma once
#include "Command.h"
#include "QBert.h"

class QBertMoveUpCommand final : public dae::Command
{
public:
	void Execute() override { GetActor()->GetComponent<dae::QBert>()->MoveUp(); }
};

class QBertMoveDownCommand final : public dae::Command
{
public:
	void Execute() override { GetActor()->GetComponent<dae::QBert>()->MoveDown(); }
};

class QBertMoveLeftCommand final : public dae::Command
{
public:
	void Execute() override { GetActor()->GetComponent<dae::QBert>()->MoveLeft(); }
};

class QBertMoveRightCommand final : public dae::Command
{
public:
	void Execute() override { GetActor()->GetComponent<dae::QBert>()->MoveRight(); }
};

