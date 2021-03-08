#pragma once

namespace dae
{
	class TextComponent;
	class GameObject;

	enum class Event
	{
		ActorHPChange,
		ActorDeath,
		PointsIncrease,
		TileChange,
		ColorChange,
		CoilyDeath,
		SlickSamCaught
	};

	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void OnNotify(const Event& event) = 0;
	};
}

