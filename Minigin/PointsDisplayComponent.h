#pragma once
#include "Observer.h"
#include "BaseComponent.h"


// This class isn't the one I use in the game for the score display
// This is just here for the sake of the Engine Demo
// (the assignments we did throughout the semester)


namespace dae
{
	class TextComponent;
	class QBertComponent;

	class PointsDisplayComponent final : public BaseComponent, public Observer
	{
	public:
		explicit PointsDisplayComponent(const std::shared_ptr<GameObject>& gameObject, QBertComponent* qBertComp);
		~PointsDisplayComponent() override;

		void SetQBert(QBertComponent* qBertComp);

		void Initialize() override;
		void Update(const float) override {}
		void OnNotify(const Event& event) override;

	private:
		TextComponent* m_TextComp{};
		QBertComponent* m_QBertComp{};
		std::shared_ptr<GameObject> m_GameObject{};
		unsigned int m_Score{};
		unsigned int m_TileChangeIncrement{};
		unsigned int m_ColorChangeIncrement{};
	};
}


