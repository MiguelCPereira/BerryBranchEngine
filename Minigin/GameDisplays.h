#pragma once
#include "Observer.h"

namespace dae
{
	class GameDisplays : public Observer
	{
	public:
		void OnNotify(BaseComponent&, Event event) override
		{
			switch(event)
			{
				case Event::ActorDied:
					std::cout << "Actor died\n";
					break;
				case Event::PointsIncreased:
					std::cout << "Points increased by 1\n";
			}
		}
	};
}

