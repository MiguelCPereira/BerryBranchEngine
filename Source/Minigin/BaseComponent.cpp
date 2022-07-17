#include "MiniginPCH.h"
#include "BaseComponent.h"

dae::BaseComponent::BaseComponent()
	: m_Subject{ new Subject() }
{}


dae::BaseComponent::~BaseComponent()
{
	delete m_Subject;
	m_Subject = nullptr;
}