#pragma once
#include "TextObject.h"

namespace dae
{
	class FPSComponent /*: public BaseComponent*/
	{
	public:
		FPSComponent() = default;
		~FPSComponent() = default;
		void Update(TextObject& text, const float deltaTime) /*override*/
		{
			m_SecCounter += deltaTime;

			m_FpsSumOverSec += int(1.f / deltaTime);
			m_Frames++;

			if (m_SecCounter >= m_RenderInterval)
			{
				const int averageFps = int(m_FpsSumOverSec / m_Frames);
				m_FpsSumOverSec = 0.f;
				m_Frames = 0;
				std::string string = std::to_string(averageFps);
				string.append(" FPS");
				text.SetText(string);

				m_SecCounter -= m_RenderInterval;
			}
		}

		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;

	private:
		float m_SecCounter = 1.0f;
		float m_RenderInterval = 1.0f;
		float m_FpsSumOverSec = 0.f;
		int m_Frames = 0;
	};
}
