#include "Coily.h"
#include "GameObject.h"
#include "GraphicsComponent.h"
#include <iostream>
#include "QBert.h"
#include "SoundServiceLocator.h"
#include "SoundSystem.h"

Coily::Coily(const std::shared_ptr<dae::GameObject>& gameObject, std::vector<QBert*>* qBertCompVector, int gameMode, int nrRows,
	float spriteWidth, float spriteHeight, int startingCube, float jumpInterval)
	: m_GameObject(gameObject)
	, m_QBertCompVector(qBertCompVector)

	, m_Alive(true)
	, m_Airborne(true)
	, m_Frozen(false)

	, m_CurrentCubeIdx(startingCube)
	, m_CurrentRow(2)
	, m_LastRow(nrRows)

	, m_SpriteWidth(spriteWidth)
	, m_SpriteHeight(spriteHeight)

	, m_JumpTimer(0.f)
	, m_JumpInterval(jumpInterval)
	, m_TransformTimer(0.f)
	, m_TransformationTime(0.9f)

	, m_Direction(startingCube - 1)
	, m_GameMode(gameMode)
	, m_CurrentState(CoilyState::ST_FallingIntoSpawn)

	, m_FallTime(0.8f)
	, m_FallHeight(155.f)
	, m_FallTimer(0.f)
	, m_FinalLandingPosY()
	, m_TimeSinceLastFrame(0.f)
	, m_FPS(50)
{
}


void Coily::SetFrozen(bool frozen)
{
	m_Frozen = frozen;
}

void Coily::Die() const
{
	//Play Sound
	m_GameObject->RemoveAllComponents();
}

bool Coily::MoveDownLeft()
{	
	if (m_Frozen == false && m_Airborne == false)
	{
		// If Coily isn't in the last pyramid row, change the pos index
		if (m_CurrentRow != m_LastRow)
		{
			m_CurrentCubeIdx = m_CurrentCubeIdx + m_CurrentRow;
			m_CurrentRow++;
		}
		else // Else, make them start hatching (but if they have already, make them jump out of the map)
		{
			if (m_CurrentState == CoilyState::ST_EggJumping)
				m_CurrentState = CoilyState::ST_Transforming;
			else
				m_Alive = false;
		}

		auto* graphics = m_GameObject->GetComponent<dae::GraphicsComponent>();
		if (m_CurrentState == CoilyState::ST_EggJumping)
		{
			graphics->SetSrcRectangle(m_SpriteWidth, 0, m_SpriteWidth, m_SpriteHeight);
			m_Airborne = true;
			m_Direction = 1;
			m_Subject->Notify(dae::Event::JumpDownLeft);
		}
		else if(m_CurrentState == CoilyState::ST_SnakeJumping || m_CurrentState == CoilyState::ST_InP2Control)
		{
			graphics->SetSrcRectangle(m_SpriteWidth * 9, 0, m_SpriteWidth, m_SpriteHeight);
			m_Airborne = true;
			m_Direction = 1;
			m_Subject->Notify(dae::Event::JumpDownLeft);
		}

		if(m_Alive)
			return true;
		else
			return false;
	}
	return false;
}

bool Coily::MoveDownRight()
{
	if (m_Frozen == false && m_Airborne == false)
	{
		// If Coily isn't in the last pyramid row, change the pos index
		if (m_CurrentRow != m_LastRow)
		{
			m_CurrentCubeIdx = m_CurrentCubeIdx + m_CurrentRow + 1;
			m_CurrentRow++;
		}
		else // Else, make them start hatching (but if they have already, make them jump out of the map)
		{
			if (m_CurrentState == CoilyState::ST_EggJumping)
				m_CurrentState = CoilyState::ST_Transforming;
			else
				m_Alive = false;
		}

		auto* graphics = m_GameObject->GetComponent<dae::GraphicsComponent>();
		if (m_CurrentState == CoilyState::ST_EggJumping)
		{
			graphics->SetSrcRectangle(m_SpriteWidth, 0, m_SpriteWidth, m_SpriteHeight);
			m_Airborne = true;
			m_Direction = 2;
			m_Subject->Notify(dae::Event::JumpDownRight);
		}
		else if (m_CurrentState == CoilyState::ST_SnakeJumping || m_CurrentState == CoilyState::ST_InP2Control)
		{
			graphics->SetSrcRectangle(m_SpriteWidth * 7, 0, m_SpriteWidth, m_SpriteHeight);
			m_Airborne = true;
			m_Direction = 2;
			m_Subject->Notify(dae::Event::JumpDownRight);
		}

		if (m_Alive)
			return true;
		else
			return false;
	}
	return false;
}

bool Coily::MoveUpLeft()
{
	if (m_Frozen == false && m_Airborne == false)
	{
		// If Coily isn't in the beginning of any of the pyramid rows, change the pos index
		if (m_CurrentCubeIdx != m_CurrentRow * (m_CurrentRow + 1) / 2 - m_CurrentRow + 1 && m_CurrentCubeIdx != 1)
		{
			m_CurrentCubeIdx = m_CurrentCubeIdx - m_CurrentRow;
			m_CurrentRow--;
		}
		else // Else, make them jump out of the map
		{
			m_Alive = false;
		}

		auto* graphics = m_GameObject->GetComponent<dae::GraphicsComponent>();
		graphics->SetSrcRectangle(m_SpriteWidth * 5, 0, m_SpriteWidth, m_SpriteHeight);

		m_Airborne = true;
		m_Direction = 3;
		m_Subject->Notify(dae::Event::JumpUpLeft);

		if (m_Alive)
			return true;
		else
			return false;
	}
	return false;
}

bool Coily::MoveUpRight()
{
	if (m_Frozen == false && m_Airborne == false)
	{
		// If Coily isn't in the end of any of the pyramid rows, change the pos index
		if (m_CurrentCubeIdx != m_CurrentRow * (m_CurrentRow + 1) / 2)
		{
			m_CurrentCubeIdx = m_CurrentCubeIdx - m_CurrentRow + 1;
			m_CurrentRow--;
		}
		else // Else, make them jump out of the map
		{
			m_Alive = false;
		}

		auto* graphics = m_GameObject->GetComponent<dae::GraphicsComponent>();
		graphics->SetSrcRectangle(m_SpriteWidth * 3, 0, m_SpriteWidth, m_SpriteHeight);

		m_Airborne = true;
		m_Direction = 4;
		m_Subject->Notify(dae::Event::JumpUpRight);

		if (m_Alive)
			return true;
		else
			return false;
	}
	return false;
}

bool Coily::MoveDownLeftPlayer()
{
	if (m_CurrentState == CoilyState::ST_InP2Control)
		return MoveDownLeft();

	return false;
}

bool Coily::MoveDownRightPlayer()
{
	if (m_CurrentState == CoilyState::ST_InP2Control)
		return MoveDownRight();

	return false;
}

bool Coily::MoveUpLeftPlayer()
{
	if (m_CurrentState == CoilyState::ST_InP2Control)
		return MoveUpLeft();

	return false;
}

bool Coily::MoveUpRightPlayer()
{
	if (m_CurrentState == CoilyState::ST_InP2Control)
		return MoveUpRight();

	return false;
}

void Coily::JumpFinished()
{
	// Set landing graphics
	auto* graphics = m_GameObject->GetComponent<dae::GraphicsComponent>();

	if (m_CurrentState == CoilyState::ST_EggJumping || m_CurrentState == CoilyState::ST_EggWaiting)
		graphics->SetSrcRectangle(0, 0, m_SpriteWidth, m_SpriteHeight);
	else
	{
		if(m_Direction == 1)
			graphics->SetSrcRectangle(m_SpriteWidth * 8, 0, m_SpriteWidth, m_SpriteHeight);
		else if(m_Direction == 2)
			graphics->SetSrcRectangle(m_SpriteWidth * 6, 0, m_SpriteWidth, m_SpriteHeight);
		else if(m_Direction == 3)
			graphics->SetSrcRectangle(m_SpriteWidth * 4, 0, m_SpriteWidth, m_SpriteHeight);
		else
			graphics->SetSrcRectangle(m_SpriteWidth * 2, 0, m_SpriteWidth, m_SpriteHeight);
	}
	
	m_Airborne = false;

	if (m_Alive)
	{
		if (m_CurrentState == CoilyState::ST_EggJumping || m_CurrentState == CoilyState::ST_EggWaiting)
			SoundServiceLocator::GetSoundSystem().Play("../Data/Sounds/Coily Egg Jump.wav", 0.1f);
		else
			SoundServiceLocator::GetSoundSystem().Play("../Data/Sounds/Coily Snake Jump.wav", 0.1f);
		
		m_Subject->Notify(dae::Event::CoilyLanded);
	}
	else
	{
		SoundServiceLocator::GetSoundSystem().Play("../Data/Sounds/Coily Fall.wav", 0.1f);
		m_Subject->Notify(dae::Event::CoilyFell);
	}
}

void Coily::Initialize()
{
	auto* graphics = m_GameObject->GetComponent<dae::GraphicsComponent>();
	m_FinalLandingPosY = graphics->GetPosY();
	graphics->SetPosition(graphics->GetPosX(), graphics->GetPosY() - m_FallHeight);
	graphics->SetSrcRectangle(m_SpriteWidth, 0, m_SpriteWidth, m_SpriteHeight);
}

void Coily::Update(const float deltaTime)
{
	switch (m_CurrentState)
	{
	case CoilyState::ST_FallingIntoSpawn:
		if (FallIntoSpawnPos(deltaTime)) // This function will only return true if the fall animation is done
		{
			m_CurrentState = CoilyState::ST_EggWaiting;
			JumpFinished();
		}
		break;
		
	case CoilyState::ST_EggWaiting:
		m_JumpTimer += deltaTime;

		if (m_JumpTimer >= m_JumpInterval)
		{
			m_JumpTimer = 0;
			m_CurrentState = CoilyState::ST_EggJumping;
		}
		break;

	case CoilyState::ST_EggJumping:
		// A random 50/50 chance of Coily's egg falling to the right or left
		if ((rand() % 2) + 1 == 1)
			MoveDownRight();
		else
			MoveDownLeft();

		if (m_CurrentState == CoilyState::ST_EggJumping) // If the egg hasn't begun transforming
			m_CurrentState = CoilyState::ST_EggWaiting;

		break;

	case CoilyState::ST_Transforming:
		m_TransformTimer += deltaTime;

		if (m_TransformTimer >= m_TransformationTime)
		{
			m_TransformTimer = 0.f;

			if (m_GameMode != 3) // If playing any mode that not Versus
			{
				m_CurrentState = CoilyState::ST_SnakeJumping;
			}
			else
			{
				// Show transformation without moving, so the player knows they now have control
				m_GameObject->GetComponent<dae::GraphicsComponent>()->SetSrcRectangle(m_SpriteWidth * 6, 0, m_SpriteWidth, m_SpriteHeight);
				m_CurrentState = CoilyState::ST_InP2Control;
			}
		}
		break;

	case CoilyState::ST_InP2Control:
		// Stop updating
		break;

	case CoilyState::ST_SnakeWaiting:
		m_JumpTimer += deltaTime;

		if (m_JumpTimer >= m_JumpInterval)
		{
			m_JumpTimer -= m_JumpInterval;
			m_CurrentState = CoilyState::ST_SnakeJumping;
		}
		break;

	case CoilyState::ST_SnakeJumping:
		// This variable prevents the timer from being reset before the movement is actually complete.
		// It will only become false if Coily's in snake mode and a QBert evades them at the last second,
		// making both Coily and the Qbert's cube index the same, although they're not colliding (has QBert's mid-air)
		// This is rare, but if it happens, the calculation will wait as many frames as it needs until QBert lands
		const bool movementSucceeded = CoilySeekBehaviour();

		if (movementSucceeded)
		{
			m_JumpTimer = 0;
			m_CurrentState = CoilyState::ST_SnakeWaiting;
		}

		break;
	}
}

bool Coily::FallIntoSpawnPos(float deltaTime)
{
	auto* graphics = m_GameObject->GetComponent<dae::GraphicsComponent>();
	const auto toTravelInSec = m_FallHeight / m_FallTime;

	m_TimeSinceLastFrame += deltaTime;
	m_FallTimer += deltaTime;

	// Change the position every 50 times per frame (or whoever much m_FPS is set as)
	if (m_TimeSinceLastFrame >= 1.f / float(m_FPS) && m_FallTimer < m_FallTime)
	{
		m_TimeSinceLastFrame -= 1.f / float(m_FPS);
		graphics->SetPosition(graphics->GetPosX(), graphics->GetPosY() + toTravelInSec / float(m_FPS));
	}

	// Stop the animation if the movement is complete
	if (m_FallTimer >= m_FallTime)
	{
		m_FallTimer = 0.f;
		graphics->SetPosition(graphics->GetPosX(), m_FinalLandingPosY);
		m_Airborne = false;
		return true;
	}

	return false;
}

bool Coily::CoilySeekBehaviour()
{
	// Calculate Coily's position in the row, counting from the right
	int coilyNrInRow;
	if (m_CurrentCubeIdx != 1)
		coilyNrInRow = (m_CurrentRow * (m_CurrentRow + 1) / 2) - m_CurrentCubeIdx;
	else
		coilyNrInRow = 0;

	// Calculate QBert 1's position in the row, counting from the right
	int qBert1NrInRow;
	const int qBert1CubeIdx = m_QBertCompVector->operator[](0)->GetPositionIndex();
	const int qBert1Row = m_QBertCompVector->operator[](0)->GetCurrentRow();
	if (qBert1CubeIdx != 1)
		qBert1NrInRow = (qBert1Row * (qBert1Row + 1) / 2) - qBert1CubeIdx;
	else
		qBert1NrInRow = 0;


	if (m_GameMode != 2) // If it's not Co-op Mode
	{
		// Follow said QBert
		return ChaseQBert(qBert1Row, qBert1NrInRow, coilyNrInRow, true);
	}
	else // If there are 2 QBerts
	{
		// Calculate QBert 2's position in the row, counting from the right
		int qBert2NrInRow;
		const int qBert2CubeIdx = m_QBertCompVector->operator[](1)->GetPositionIndex();
		const int qBert2Row = m_QBertCompVector->operator[](1)->GetCurrentRow();
		if (qBert2CubeIdx != 1)
			qBert2NrInRow = (qBert2Row * (qBert2Row + 1) / 2) - qBert2CubeIdx;
		else
			qBert2NrInRow = 0;


		const int p1Distance = CalculateQBertDistance(qBert1Row, qBert1NrInRow, coilyNrInRow);
		const int p2Distance = CalculateQBertDistance(qBert2Row, qBert2NrInRow, coilyNrInRow);

		if (p1Distance < p2Distance)
			return ChaseQBert(qBert1Row, qBert1NrInRow, coilyNrInRow, true);
		else
			return ChaseQBert(qBert2Row, qBert2NrInRow, coilyNrInRow, false);
	}
}

bool Coily::ChaseQBert(int qBertRow, int qBertNrInRow, int coilyNrInRow, bool isPlayerOne)
{
	if (qBertRow > m_CurrentRow) // QBert is bellow Coily
	{
		if (qBertNrInRow > coilyNrInRow) // Qbert is to Coily's Left
			MoveDownLeft();
		else // Qbert is either to Coily's Right or exactly bellow
			MoveDownRight();

		return true;
	}
	else if (qBertRow < m_CurrentRow) // QBert is above Coily
	{
		if (qBertNrInRow < coilyNrInRow) // Qbert is to Coily's Right
			MoveUpRight();
		else // Qbert is either to Coily's Right or exactly above
			MoveUpLeft();

		return true;
	}
	else // They're both in the same row
	{
		// Coily will always move up in these situations
		// (unless QBert isn't actually in the same tile anymore, just mid-fight, as I explain bellow)
		// because if they went down and they happened to be in the last row
		// they would jump to their death

		if (qBertNrInRow < coilyNrInRow) // QBert is to Coily's Right
		{
			MoveUpRight();
			return true;
		}
		else if (qBertNrInRow > coilyNrInRow)// QBert's to Coily's Left
		{
			MoveUpLeft();
			return true;
		}
		else // Coily's in the same cube has Qbert's last index
		{
			if (isPlayerOne)
			{
				if (m_QBertCompVector->operator[](0)->GetIsInDisk()) // If QBert has taken a disk
				{
					// Make Coily jump to their death, depending on which direction QBert jumped to last
					if (m_QBertCompVector->operator[](0)->GetLastJumpedOffLeft())
						MoveUpLeft();
					else
						MoveUpRight();

					return true;
				}
				else // QBert evaded right at the last second and is now still mid-jump, wait for them to land before moving
				{
					return false;
				}
			}
			else
			{
				if (m_QBertCompVector->operator[](1)->GetIsInDisk()) // If QBert has taken a disk
				{
					// Make Coily jump to their death, depending on which direction QBert jumped to last
					if (m_QBertCompVector->operator[](1)->GetLastJumpedOffLeft())
						MoveUpLeft();
					else
						MoveUpRight();

					return true;
				}
				else // QBert might've evaded right at the last second and is now still mid-jump, wait for them to land before moving
				{
					return false;
				}
			}
		}
	}
}

int Coily::CalculateQBertDistance(int qBertRow, int qBertNrInRow, int coilyNrInRow) const
{
	int distance = 0;
	
	// If QBert's above Coily
	if (qBertRow > m_CurrentRow)
	{
		distance += qBertRow - m_CurrentRow; // Each row difference means 1 move

		if (qBertNrInRow > coilyNrInRow) // And each cube difference horizontally means 2 moves
			distance = qBertNrInRow - coilyNrInRow;
		else
			distance = coilyNrInRow - qBertNrInRow;
	}
	else // If QBert's bellow or in the same row as Coily
	{
		distance += m_CurrentRow - qBertRow; // Each row difference still means 1 move

		int distHorizontal;
		if (qBertNrInRow > coilyNrInRow)
			distHorizontal = qBertNrInRow - coilyNrInRow;
		else
			distHorizontal = coilyNrInRow - qBertNrInRow;

		if (distHorizontal > distance)
			distance = (distHorizontal - distance) * 2; // But the horizontal difference only takes more moves if it's bigger than the row difference
	}

	return distance;
}




