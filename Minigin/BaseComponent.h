#pragma once

namespace dae
{
	class TextObject;
	class Texture2D;
	class Transform;
	class GameObject;

	class BaseComponent
	{
	public:
		virtual void Update(GameObject& gameObject, Transform& transform, std::shared_ptr<Texture2D> pTexture, const float deltaTime) = 0;
		//virtual void Update(TextObject& textObject, const float deltaTime) = 0;
		virtual ~BaseComponent() = default;
	};
}

