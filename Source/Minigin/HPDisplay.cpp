#include "MiniginPCH.h"
#include "HPDisplay.h"
#include "TextComponent.h"
#include <iostream>


// This class isn't the one I use in the game for the lives display
// This is just here for the sake of the Engine Demo
// (the assignments we did throughout the semester)


dae::HPDisplay::HPDisplay(TextComponent* textComp)
	: m_TextComponent(textComp)
{}

void dae::HPDisplay::OnNotify(const Event& event)
{
	std::string string = "Remaining Lives: ";
	int actorHP;
	
	switch (event)
	{
	case Event::ActorHPChange:
		actorHP = 8; // Need to change this for the actor real HP
		string.append(std::to_string(actorHP));
		//m_TextComponent->SetText(string);
		break;
	case Event::ActorDeath:
		//m_TextComponent->SetText("Actor Died");
		break;
	case Event::PointsIncrease:
		std::cout << "Points increased by 1\n";
	}
}