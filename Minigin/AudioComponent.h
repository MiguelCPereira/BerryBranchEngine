#pragma once
#include "BaseComponent.h"

namespace dae
{
	class AudioComponent : public BaseComponent
	{
	public:
		virtual ~AudioComponent() = default;
		virtual void Update(GameObject& gameObject, Transform& transform, std::shared_ptr<Texture2D> pTexture, const float deltaTime) = 0;
	};
}

