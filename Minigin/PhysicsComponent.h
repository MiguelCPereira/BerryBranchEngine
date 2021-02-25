#pragma once
#include "BaseComponent.h"
#include "GameObject.h"
#include "Transform.h"

namespace dae
{
	class PhysicsComponent : public BaseComponent
	{
	public:
		virtual ~PhysicsComponent() = 0;
		virtual void Update(GameObject& gameObject, Transform& transform, std::shared_ptr<Texture2D> pTexture, const float deltaTime, TextObject textObject) = 0;
	};
}

