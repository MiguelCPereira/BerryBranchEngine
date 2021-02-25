#pragma once
#include "TextObject.h"
//#include "BaseComponent.h"

namespace dae
{
	class HPTextComponent /*: public BaseComponent*/
	{
	public:
		HPTextComponent() = default;
		~HPTextComponent() = default;
		void Update(TextObject& text, const float) const /*override*/
		{
			std::string string{ "Remaining Lives: " };
			// Get the current hp from the Observer
			string.append("3");
			text.SetText(string);
		}

		HPTextComponent(const HPTextComponent& other) = delete;
		HPTextComponent(HPTextComponent&& other) = delete;
		HPTextComponent& operator=(const HPTextComponent& other) = delete;
		HPTextComponent& operator=(HPTextComponent&& other) = delete;
	};
}

