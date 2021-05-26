#pragma once
#include "Observer.h"


// This class isn't the one I use in the game for the lives display
// This is just here for the sake of the Engine Demo
// (the assignments we did throughout the semester)


namespace dae
{
	class HPDisplay : public Observer
	{
	public:
		HPDisplay(TextComponent* textComp);
		void OnNotify(const Event& event) override;

	private:
		TextComponent* m_TextComponent;
	};
}

