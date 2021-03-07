#pragma once
#include "BaseComponent.h"

namespace dae
{
	class InputComponent : public BaseComponent
	{
	public:
		explicit InputComponent() = default;
		virtual ~InputComponent() = default;

		InputComponent(const InputComponent& other) = delete;
		InputComponent(InputComponent&& other) = delete;
		InputComponent& operator=(const InputComponent& other) = delete;
		InputComponent& operator=(InputComponent&& other) = delete;
		
		virtual void Update(const float deltaTime) = 0;
	};
}

