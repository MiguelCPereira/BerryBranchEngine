#pragma once
#include <vector>
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
		m_Observers.erase(std::remove(m_Observers.begin(), m_Observers.end(), observer), m_Observers.end());
	}
	void Notify(dae::Event event)
	{
		for( auto observer : m_Observers )
		{
			observer->OnNotify(event);
		}
	}

private:
	std::vector<dae::Observer*> m_Observers;
};

