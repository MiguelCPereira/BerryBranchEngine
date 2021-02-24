#pragma once

namespace dae
{
	class Texture2D;
	class Transform;
	class GameObject;

	class BaseComponent
	{
	public:
		virtual void Update(GameObject& gameObject, Transform& transform, std::shared_ptr<Texture2D> pTexture, const float deltaTime) = 0;
		BaseComponent() = default;
		virtual ~BaseComponent() = default;

		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;
	};
}

