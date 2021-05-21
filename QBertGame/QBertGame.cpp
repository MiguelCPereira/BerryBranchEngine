// Project includes
#include <memory>
#include<string>
#include "QBert.h"
#include "Pyramid.h"

// Engine includes - I later on intend on making a factory class, so most of these includes are temporary
#include <Minigin.h>
#include "Scene.h"
#include "GraphicsComponent.h"
#include "GameObject.h"
#include "QBertComponent.h" // This class is the same as "QBert" and will eventually be deleted, it only exists for now as to not crash the engine demo
#include "ResourceManager.h"
#include "SoundServiceLocator.h"
#include "FPSComponent.h"
//#include "LivesDisplayComponent.h"
//#include "PointsDisplayComponent.h"
#include "TextComponent.h"
#include "Command.h"

#include "InputManager.h"
#include <SDL.h>

#include "GameCommands.h"

void LoadDemo();
void LoadGame();

int main(int, char* [])
{
    dae::Minigin engine;
    engine.Initialize();
    LoadGame();	
    engine.Run();	
    return 0;
}


void LoadGame()
{
	const int nrRows = 7;
	const float cubesWidth = 56.f;
	const float cubesHeight = 56.f;
	
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Game");

	// Level Map
	Pyramid pyramid(300.f, 80.f, nrRows, cubesWidth, cubesHeight);
	for (auto cube : pyramid.m_CubeGOVector)
		scene.Add(cube);
	
	// QBert
	auto qBertGO = std::make_shared<dae::GameObject>();
	qBertGO->AddComponent(new dae::QBert(qBertGO, nrRows, cubesWidth, cubesHeight));
	qBertGO->AddComponent(new dae::GraphicsComponent("qBert.png", 312, 50, 40, 49));
	scene.Add(qBertGO);

	// Input
	auto moveUpKeyboard = std::make_unique<QBertMoveUpCommand>();
	moveUpKeyboard->SetActor(qBertGO);
	moveUpKeyboard->SetButtonPressType(dae::ButtonPress::PressedDown);
	dae::InputManager::GetInstance().AddCommand(SDLK_w, std::move(moveUpKeyboard));

	auto moveDownKeyboard = std::make_unique<QBertMoveDownCommand>();
	moveDownKeyboard->SetActor(qBertGO);
	moveDownKeyboard->SetButtonPressType(dae::ButtonPress::PressedDown);
	dae::InputManager::GetInstance().AddCommand(SDLK_s, std::move(moveDownKeyboard));

	auto moveLeftKeyboard = std::make_unique<QBertMoveLeftCommand>();
	moveLeftKeyboard->SetActor(qBertGO);
	moveLeftKeyboard->SetButtonPressType(dae::ButtonPress::PressedDown);
	dae::InputManager::GetInstance().AddCommand(SDLK_a, std::move(moveLeftKeyboard));

	auto moveRightKeyboard = std::make_unique<QBertMoveRightCommand>();
	moveRightKeyboard->SetActor(qBertGO);
	moveRightKeyboard->SetButtonPressType(dae::ButtonPress::PressedDown);
	dae::InputManager::GetInstance().AddCommand(SDLK_d, std::move(moveRightKeyboard));
	
	scene.Initialize();

	// Instructions
	std::cout << "Controls:\n";
	std::cout << "\n";
	std::cout << "   W   | Move Up/Right\n";
	std::cout << "   S   | Move Down/Left\n";
	std::cout << "   A   | Move Up/Left\n";
	std::cout << "   D   | Move Down/Right\n\n";
	std::cout << "The player input is still not implemented\n\n";
}

void LoadDemo()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	// DAE Background
	auto gameObject = std::make_shared<dae::GameObject>();
	gameObject->AddComponent(new dae::GraphicsComponent("background.jpg"));
	scene.Add(gameObject);


	// DAE Logo
	gameObject = std::make_shared<dae::GameObject>();
	gameObject->AddComponent(new dae::GraphicsComponent("logo.png", 216, 180));
	scene.Add(gameObject);

	// Engine Title
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	gameObject = std::make_shared<dae::GameObject>();
	
	// Any action that involves Transform leads to a crash right now
	// Because transform pointers are all messed up for some reason and return null
	// So the creation of a TextComponent will always crash,
	// as well as trying to change the position of a GameObject
	
	//gameObject->AddComponent(new dae::TextComponent("Programming 4 Assignment", font));
	//gameObject->GetComponent<dae::TextComponent>()->SetPosition(80, 20);
	scene.Add(gameObject);


	// FPS Counter
	//font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 19);
	//gameObject = std::make_shared<dae::GameObject>();
	//gameObject->AddComponent(new dae::FPSComponent(gameObject));
	//gameObject->AddComponent(new dae::TextComponent("FAIL FPS", font, 255, 255, 0));
	//gameObject->GetComponent<dae::TextComponent>()->SetPosition(5, 5);
	//scene.Add(gameObject);
	
	// QBert
	auto qBertGameObject = std::make_shared<dae::GameObject>();
	qBertGameObject->AddComponent(new dae::QBertComponent(qBertGameObject));
	qBertGameObject->AddComponent(new dae::GraphicsComponent("qBert.png", 50, 270));
	scene.Add(qBertGameObject);


	// Input
	auto dieKeyboard = std::make_unique<dae::DieCommand>();
	dieKeyboard->SetActor(qBertGameObject);
	dieKeyboard->SetButtonPressType(dae::ButtonPress::PressedDown);
	dae::InputManager::GetInstance().AddCommand(SDLK_q, std::move(dieKeyboard));

	auto colorChangeKeyboard = std::make_unique<dae::ColorChangeCommand>();
	colorChangeKeyboard->SetActor(qBertGameObject);
	colorChangeKeyboard->SetButtonPressType(dae::ButtonPress::PressedDown);
	dae::InputManager::GetInstance().AddCommand(SDLK_w, std::move(colorChangeKeyboard));

	auto tileChangeKeyboard = std::make_unique<dae::TileChangeCommand>();
	tileChangeKeyboard->SetActor(qBertGameObject);
	tileChangeKeyboard->SetButtonPressType(dae::ButtonPress::PressedDown);
	dae::InputManager::GetInstance().AddCommand(SDLK_e, std::move(tileChangeKeyboard));

	auto playSoundKeyboard = std::make_unique<dae::PlaySoundCommand>(&SoundServiceLocator::GetSoundSystem());
	playSoundKeyboard->SetActor(qBertGameObject);
	playSoundKeyboard->SetButtonPressType(dae::ButtonPress::PressedDown);
	dae::InputManager::GetInstance().AddCommand(SDLK_SPACE, std::move(playSoundKeyboard));


	// Lives Displays
	//font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 25);
	//gameObject = std::make_shared<dae::GameObject>();
	//gameObject->AddComponent(new dae::TextComponent("Remaining Lives: FAIL", font));
	//gameObject->GetComponent<dae::TextComponent>()->SetPosition(13, 140);
	//gameObject->AddComponent(new dae::LivesDisplayComponent(gameObject, qBertGameObject->GetComponent<dae::QBertComponent>()));
	//scene.Add(gameObject);


	// Points Displays
	//font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 25);
	//gameObject = std::make_shared<dae::GameObject>();
	//gameObject->AddComponent(new dae::TextComponent("Points: FAIL", font));
	//gameObject->GetComponent<dae::TextComponent>()->SetPosition(70, 180);
	//gameObject->AddComponent(new dae::PointsDisplayComponent(gameObject, qBertGameObject->GetComponent<dae::QBertComponent>()));
	//scene.Add(gameObject);

	
	
	// 2nd QBert
	auto qBertGameObject2 = std::make_shared<dae::GameObject>();
	qBertGameObject2->AddComponent(new dae::QBertComponent(qBertGameObject2));
	qBertGameObject2->AddComponent(new dae::GraphicsComponent("qBert.png", 445, 270));
	scene.Add(qBertGameObject2);

	auto dieKeyboard2 = std::make_unique<dae::DieCommand>();
	dieKeyboard2->SetActor(qBertGameObject2);
	dieKeyboard2->SetButtonPressType(dae::ButtonPress::PressedDown);
	dae::InputManager::GetInstance().AddCommand(SDLK_i, std::move(dieKeyboard2));
	auto colorChangeKeyboard2 = std::make_unique<dae::ColorChangeCommand>();
	colorChangeKeyboard2->SetActor(qBertGameObject2);
	colorChangeKeyboard2->SetButtonPressType(dae::ButtonPress::PressedDown);
	dae::InputManager::GetInstance().AddCommand(SDLK_o, std::move(colorChangeKeyboard2));
	auto tileChangeKeyboard2 = std::make_unique<dae::TileChangeCommand>();
	tileChangeKeyboard2->SetActor(qBertGameObject2);
	tileChangeKeyboard2->SetButtonPressType(dae::ButtonPress::PressedDown);
	dae::InputManager::GetInstance().AddCommand(SDLK_p, std::move(tileChangeKeyboard2));

	//font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 25);
	//gameObject = std::make_shared<dae::GameObject>();
	//gameObject->AddComponent(new dae::TextComponent("Remaining Lives: FAIL", font));
	//gameObject->GetComponent<dae::TextComponent>()->SetPosition(408, 140);
	//gameObject->AddComponent(new dae::LivesDisplayComponent(gameObject, qBertGameObject2->GetComponent<dae::QBertComponent>()));
	//scene.Add(gameObject);

	//font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 25);
	//gameObject = std::make_shared<dae::GameObject>();
	//gameObject->AddComponent(new dae::TextComponent("Points: FAIL", font));
	//gameObject->GetComponent<dae::TextComponent>()->SetPosition(465, 180);
	//gameObject->AddComponent(new dae::PointsDisplayComponent(gameObject, qBertGameObject2->GetComponent<dae::QBertComponent>()));

	scene.Add(gameObject);


	
	// Instructions
	std::cout << "Controls:\n";
	std::cout << "\n";
	std::cout << "   Q   | Kill 1st QBert\n";
	std::cout << "   W   | Change Color of 1st QBert (gain 10 points)\n";
	std::cout << "   E   | Change Tile of 1st QBert (gain 25 points)\n";
	std::cout << "   I   | Kill 2nd QBert\n";
	std::cout << "   O   | Change Color of 2nd QBert (gain 10 points)\n";
	std::cout << "   P   | Change Tile of 2nd QBert (gain 25 points)\n";
	std::cout << " SPACE | Make a jump sound\n\n";
	
    scene.Initialize();
}
