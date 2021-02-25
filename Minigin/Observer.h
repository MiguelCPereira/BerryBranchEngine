#pragma once

namespace dae
{
	class GameObject;
	class SDL_Event;

	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void OnNotify(const GameObject& entity, SDL_Event event) = 0;
	};
}

