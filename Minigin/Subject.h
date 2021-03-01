#pragma once
#include "Observer.h"

class Subject
{
public:
	void AddObserver(dae::Observer* observer)
	{
		m_Observers.push_back(observer);
	}

	void RemoveObserver(dae::Observer* observer)
	{
		const auto observerPos = std::find(m_Observers.begin(), m_Observers.end(), observer);
		if (observerPos != m_Observers.end())
			m_Observers.erase(observerPos);
	}
	void Notify(dae::BaseComponent& entity, dae::Event event)
	{
		for( auto observer : m_Observers )
		{
			observer->OnNotify(entity, event);
		}
	}

private:
	std::vector<dae::Observer*> m_Observers;
};

