#pragma once
#include "Observer.h"

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

