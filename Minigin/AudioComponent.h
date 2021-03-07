#pragma once
#include "BaseComponent.h"

namespace dae
{
	class AudioComponent : public BaseComponent
	{
	public:
		explicit AudioComponent() = default;
		virtual ~AudioComponent() = default;

		AudioComponent(const AudioComponent& other) = delete;
		AudioComponent(AudioComponent&& other) = delete;
		AudioComponent& operator=(const AudioComponent& other) = delete;
		AudioComponent& operator=(AudioComponent&& other) = delete;
		
		virtual void Update(const float deltaTime) = 0;
	};
}

