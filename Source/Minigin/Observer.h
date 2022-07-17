#pragma once

namespace dae
{
	class TextComponent;
	class GameObject;

	enum class Event
	{
		// Only the engine demo uses these
		ActorHPChange,
		ActorDeath,
		PointsIncrease,
		SlickSamCaught,
		TileChange,
		ColorChange,


		// These are the actual game events
		EntityFrozen,
		EntityUnfrozen,
		EntityAnimationStopped,
		
		CoilyLanded,
		CoilyFell,
		
		ScoreIncreasedP1,
		QBertDiedP1,
		QBertLandedP1,
		QBertFellP1,

		ScoreIncreasedP2,
		QBertDiedP2,
		QBertLandedP2,
		QBertFellP2,
		
		SlickSamLanded,
		SlickSamFell,
		UggWrongwayLanded,
		UggWrongwayFell,
		
		JumpUpRight,
		JumpUpLeft,
		JumpDownRight,
		JumpDownLeft,
		JumpLeft,
		JumpRight,
		
		LevelUpdated,
		RoundUpdated,
		
		DiskFlightEndedP1,
		DiskFlightEndedP2,

		CoilyHitQBert,

		PausePressed,
		BackToMenu
	};

	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void OnNotify(const Event& event) = 0;
	};
}

