#include "MiniginPCH.h"
#include "HPDisplay.h"
#include "TextComponent.h"
#include <iostream>

dae::HPDisplay::HPDisplay(TextComponent* textComp)
	: m_TextComponent(textComp)
{}

void dae::HPDisplay::OnNotify(const Event& event)
{
	std::string string = "Remaining Lives: ";
	int actorHP;
	
	switch (event)
	{
	case Event::ActorHPChanged:
		actorHP = 8; // Need to change this for the actor real HP
		string.append(std::to_string(actorHP));
		//m_TextComponent->SetText(string);
		break;
	case Event::ActorDied:
		//m_TextComponent->SetText("Actor Died");
		break;
	case Event::PointsIncreased:
		std::cout << "Points increased by 1\n";
	}
}