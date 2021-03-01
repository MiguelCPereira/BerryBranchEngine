#pragma once

namespace dae
{
	class BaseComponent;

	enum class Event
	{
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
		virtual void OnNotify(BaseComponent& entity, Event event) = 0;
	};
}

