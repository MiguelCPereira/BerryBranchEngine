#pragma once

namespace dae
{
	class TextComponent;
	class GameObject;

	// Need to make this editable outside of the engine
	enum class Event
	{
		// Only the engine demo uses these
		ActorHPChange,
		ActorDeath,
		PointsIncrease,
		SlickSamCaught,
		TileChange,
		ColorChange,


		// While these are only used in the game
		CoilyLanded,
		CoilyFell,
		ScoreIncreased,
		QBertDied,
		QBertLanded,
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
		RoundUpdated
	};

	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void OnNotify(const Event& event) = 0;
	};
}

