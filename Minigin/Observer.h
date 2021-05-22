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
		
		QBertMove,
		SlickSamMove
	};

	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void OnNotify(const Event& event) = 0;
	};
}

