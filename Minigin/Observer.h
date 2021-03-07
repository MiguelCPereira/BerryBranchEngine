#pragma once

namespace dae
{
	class TextComponent;
	class GameObject;

	enum class Event
	{
		ActorHPChanged,
		ActorDied,
		PointsIncreased,
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

