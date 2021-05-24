#pragma once

namespace dae
{
	class TextComponent;
	class GameObject;

	// Need to make this editable outside of the engine
	enum class Event
	{
		ActorHPChange,
		ActorDeath,
		PointsIncrease,
		TileChange,
		ColorChange,
		CoilyDeath,
		SlickSamCaught,
		
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
		JumpRight
	};

	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void OnNotify(const Event& event) = 0;
	};
}

