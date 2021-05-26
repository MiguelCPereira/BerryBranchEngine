#pragma once
#include "Observer.h"
#include "BaseComponent.h"


// This class isn't the one I use in the game for the lives display
// This is just here for the sake of the Engine Demo
// (the assignments we did throughout the semester)


namespace dae
{
	class TextComponent;
	class QBertComponent;
	
	class LivesDisplayComponent final : public BaseComponent, public Observer
	{
	public:
		explicit LivesDisplayComponent(const std::shared_ptr<GameObject>& gameObject, QBertComponent* qBertComp);
		~LivesDisplayComponent() override;

		void SetQBert(QBertComponent* qBertComp);

		void Initialize() override;
		void Update(const float) override {}
		void OnNotify(const Event& event) override;
	
	private:
		TextComponent* m_TextComp{};
		QBertComponent* m_QBertComp{};
		std::shared_ptr<GameObject> m_GameObject{};
	};
}

