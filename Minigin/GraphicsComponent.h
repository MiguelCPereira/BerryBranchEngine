#pragma once
#include "BaseComponent.h"
#include "Renderer.h"
#include "Transform.h"

namespace dae
{
	class GraphicsComponent : public BaseComponent
	{
	public:
		virtual ~GraphicsComponent() = default;
		virtual void Update(GameObject&, Transform& transform, std::shared_ptr<Texture2D> pTexture, const float)
		{
			const auto pos = transform.GetPosition();
			dae::Renderer::GetInstance().RenderTexture(*pTexture, pos.x, pos.y);
		}
	};
}