#pragma once
#include "BaseComponent.h"
#include "Transform.h"

namespace dae
{
	class PhysicsComponent : public BaseComponent
	{
	public:
		virtual ~PhysicsComponent() = default;
		virtual void Update(GameObject& gameObject, Transform& transform, std::shared_ptr<Texture2D> pTexture, const float deltaTime) = 0;

		PhysicsComponent(const PhysicsComponent& other) = delete;
		PhysicsComponent(PhysicsComponent&& other) = delete;
		PhysicsComponent& operator=(const PhysicsComponent& other) = delete;
		PhysicsComponent& operator=(PhysicsComponent&& other) = delete;
	};
}

