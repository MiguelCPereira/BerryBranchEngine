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

		InputComponent(const InputComponent& other) = delete;
		InputComponent(InputComponent&& other) = delete;
		InputComponent& operator=(const InputComponent& other) = delete;
		InputComponent& operator=(InputComponent&& other) = delete;
	};
}

