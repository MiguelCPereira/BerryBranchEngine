#pragma once
#include "Subject.h"

namespace dae
{
	class GameObject;

	class BaseComponent
	{
	public:
		BaseComponent();
		virtual ~BaseComponent();

		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) noexcept = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) noexcept = delete;
		
		virtual void Update(const float deltaTime) = 0;
		virtual void Initialize() {}
		virtual void Render() const {}
		Subject* GetSubject() const { return m_Subject; }

	protected:
		Subject* m_Subject;
	};
}

