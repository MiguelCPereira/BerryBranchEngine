#pragma once
#include "BaseComponent.h"

namespace dae
{
	class PhysicsComponent : public BaseComponent
	{
	public:
		explicit PhysicsComponent() = default;
		virtual ~PhysicsComponent() = 0;

		PhysicsComponent(const PhysicsComponent& other) = delete;
		PhysicsComponent(PhysicsComponent&& other) = delete;
		PhysicsComponent& operator=(const PhysicsComponent& other) = delete;
		PhysicsComponent& operator=(PhysicsComponent&& other) = delete;
		
		virtual void Update(const float deltaTime) = 0;
	};
}

