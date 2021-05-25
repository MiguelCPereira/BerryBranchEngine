#pragma once
#include "BaseComponent.h"

namespace dae
{
	class TextComponent;
	
	class FPSComponent final : public BaseComponent
	{
	public:
		MINIGIN_ENTRY FPSComponent(std::shared_ptr<GameObject> ownerObject);
		~FPSComponent() = default;
		
		void Initialize() override;
		void Update(const float deltaTime) override;

		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;

	private:
		std::shared_ptr<GameObject> m_GameObject;
		TextComponent* m_Text = nullptr;
		float m_SecCounter = 1.0f;
		float m_RenderInterval = 1.0f;
		float m_FpsSumOverSec = 0.f;
		int m_Frames = 0;
	};
}
