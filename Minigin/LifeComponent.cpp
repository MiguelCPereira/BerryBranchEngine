#include "MiniginPCH.h"
#include "LifeComponent.h"
#include "Subject.h"
//#include "GameDisplays.h"

dae::LifeComponent::LifeComponent(int maxHP)
	: m_MaxHealth(maxHP),
	m_Health(maxHP),
	m_Alive(true)
{}

void dae::LifeComponent::Update(const float)
{}

void dae::LifeComponent::GetDamaged(int damageAmount)
{
	if (damageAmount < 0)
	{
		std::cout << "Can't deal negative damage, to heal use the GetHealed function";
	}
	else
	{
		if (m_Health - damageAmount > 0)
		{
			m_Health -= damageAmount;
			m_Subject->Notify(Event::ActorHPChange);
		}
		else
		{
			m_Health = 0;
			m_Alive = false;
			m_Subject->Notify(Event::ActorDeath);
		}
	}
}

void dae::LifeComponent::GetHealed(int healAmount)
{
	if (healAmount < 0)
	{
		std::cout << "Can't heal negative quantities, to deal damage use the GetDamaged function";
	}
	else
	{
		if (m_Health + healAmount > m_MaxHealth)
		{
			m_Health = m_MaxHealth;
		}
		else
		{
			m_Health += healAmount;
		}
	}
}