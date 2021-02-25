#pragma once
#include "BaseComponent.h"
#include "Transform.h"

namespace dae
{
	class InputComponent : public BaseComponent
	{
	public:
		virtual ~InputComponent() = default;
		virtual void Update(GameObject& gameObject, Transform& transform, std::shared_ptr<Texture2D> pTexture, const float deltaTime) = 0;
	};
}

