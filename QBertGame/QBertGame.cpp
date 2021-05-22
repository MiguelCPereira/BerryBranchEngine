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
//#include "GameObserver.h"
#include "LevelSectionObserver.h"




// Global Variables
const int g_NrRows = 7;
const float g_CubesActualWidth = 56.f;
const float g_CubesActualHeight = 56.f;
const int g_CubesSpriteWidth = 32;
const int g_CubesSpriteHeight = 32;
std::shared_ptr<dae::GameObject> g_QBertGO;
//std::shared_ptr<dae::GameObject> g_GameObserverGO;


// Global Functions
void SetUpGlobalGOs();
void LoadDemo();
void LoadLevel01();
void LoadLevel02();
void LoadLevel03();
void LoadLevel04();
void PrintInstructions();




int main(int, char* [])
{
    dae::Minigin engine;
    engine.Initialize();

	SetUpGlobalGOs();
	LoadLevel01();
	LoadLevel02();
	LoadLevel03();
	PrintInstructions();

	
	engine.Run();
	
    return 0;
}




void LoadLevel01()
{
	//// All Level Sections Observers GameObjects
	auto sectionObserverGO1 = std::make_shared<dae::GameObject>();
	auto sectionObserverGO2 = std::make_shared<dae::GameObject>();
	auto sectionObserverGO3 = std::make_shared<dae::GameObject>();
	auto sectionObserverGO4 = std::make_shared<dae::GameObject>();
	
	//auto* sectionsVector = new std::vector<std::shared_ptr<dae::GameObject>>;
	//sectionsVector->push_back(sectionObserverGO1);
	//sectionsVector->push_back(sectionObserverGO2);
	//sectionsVector->push_back(sectionObserverGO3);
	//sectionsVector->push_back(sectionObserverGO4);

	
	//// Section 01

	// Create Scene
	auto& scene1 = dae::SceneManager::GetInstance().CreateScene("Level01A");

	// Level Map
	auto* pyramid = new Pyramid(300.f, 80.f, g_NrRows, g_CubesActualWidth, g_CubesActualHeight,
		0, 1, g_CubesSpriteWidth, g_CubesSpriteHeight);
	for (const std::shared_ptr<dae::GameObject>& cube : pyramid->m_CubeGOVector)
		scene1.Add(cube);

	// Transfer QBert
	scene1.Add(g_QBertGO);

	// Level Section Observer
	sectionObserverGO1->AddComponent(new LevelSectionObserver(sectionObserverGO1, g_QBertGO->GetComponent<dae::QBert>(), pyramid));
	scene1.Add(sectionObserverGO1);

	// Transfer Game Observer
	//g_GameObserverGO->AddComponent(new GameObserver(g_GameObserverGO, sectionObserverGO1->GetComponent<LevelSectionObserver>()));
	//scene1.Add(g_GameObserverGO);

	// Initialize Scene
	scene1.Initialize();

	
	//////////////////////////


	//// Section 02
	
	// Create Scene
	auto& scene2 = dae::SceneManager::GetInstance().CreateScene("Level01B");

	// Level Map
	pyramid = new Pyramid(300.f, 80.f, g_NrRows, g_CubesActualWidth, g_CubesActualHeight,
		1, 1, g_CubesSpriteWidth, g_CubesSpriteHeight);
	for (const std::shared_ptr<dae::GameObject>& cube : pyramid->m_CubeGOVector)
		scene2.Add(cube);

	// Transfer QBert
	scene2.Add(g_QBertGO);

	// Level Section Observer
	sectionObserverGO2->AddComponent(new LevelSectionObserver(sectionObserverGO2, g_QBertGO->GetComponent<dae::QBert>(), pyramid));
	scene2.Add(sectionObserverGO2);

	// Transfer Game Observer
	//scene2.Add(g_GameObserverGO);


	//////////////////////////


	//// Section 03
	
	// Create Scene
	auto& scene3 = dae::SceneManager::GetInstance().CreateScene("Level01C");

	// Level Map
	pyramid = new Pyramid(300.f, 80.f, g_NrRows, g_CubesActualWidth, g_CubesActualHeight,
		2, 1, g_CubesSpriteWidth, g_CubesSpriteHeight);
	for (const std::shared_ptr<dae::GameObject>& cube : pyramid->m_CubeGOVector)
		scene3.Add(cube);

	// Transfer QBert
	scene3.Add(g_QBertGO);

	// Level Section Observer
	sectionObserverGO3 = std::make_shared<dae::GameObject>();
	sectionObserverGO3->AddComponent(new LevelSectionObserver(sectionObserverGO3, g_QBertGO->GetComponent<dae::QBert>(), pyramid));
	scene3.Add(sectionObserverGO3);

	// Transfer Game Observer
	//scene3.Add(g_GameObserverGO);


	//////////////////////////


	//// Section 04
	
	// Create Scene
	auto& scene4 = dae::SceneManager::GetInstance().CreateScene("Level01D");

	// Level Map
	pyramid = new Pyramid(300.f, 80.f, g_NrRows, g_CubesActualWidth, g_CubesActualHeight,
		3, 1, g_CubesSpriteWidth, g_CubesSpriteHeight);
	for (const std::shared_ptr<dae::GameObject>& cube : pyramid->m_CubeGOVector)
		scene4.Add(cube);

	// Transfer QBert
	scene4.Add(g_QBertGO);

	// Level Section Observer
	sectionObserverGO4 = std::make_shared<dae::GameObject>();
	sectionObserverGO4->AddComponent(new LevelSectionObserver(sectionObserverGO4, g_QBertGO->GetComponent<dae::QBert>(), pyramid));
	scene4.Add(sectionObserverGO4);

	// Transfer Game Observer
	//scene4.Add(g_GameObserverGO);
}

void LoadLevel02()
{
	//// Section 01

	// Create Scene
	auto& scene1 = dae::SceneManager::GetInstance().CreateScene("Level02A");

	// Level Map
	auto* pyramid = new Pyramid(300.f, 80.f, g_NrRows, g_CubesActualWidth, g_CubesActualHeight,
		1, 2, g_CubesSpriteWidth, g_CubesSpriteHeight);
	for (const std::shared_ptr<dae::GameObject>& cube : pyramid->m_CubeGOVector)
		scene1.Add(cube);

	// Transfer QBert
	scene1.Add(g_QBertGO);

	// Level Section Observer
	auto sectionObserverGO = std::make_shared<dae::GameObject>();
	sectionObserverGO->AddComponent(new LevelSectionObserver(sectionObserverGO, g_QBertGO->GetComponent<dae::QBert>(), pyramid));
	scene1.Add(sectionObserverGO);

	// Transfer Game Observer
	//scene1.Add(g_GameObserverGO);


	//////////////////////////


	//// Section 02

	// Create Scene
	auto& scene2 = dae::SceneManager::GetInstance().CreateScene("Level02B");

	// Level Map
	pyramid = new Pyramid(300.f, 80.f, g_NrRows, g_CubesActualWidth, g_CubesActualHeight,
		3, 2, g_CubesSpriteWidth, g_CubesSpriteHeight);
	for (const std::shared_ptr<dae::GameObject>& cube : pyramid->m_CubeGOVector)
		scene2.Add(cube);

	// Transfer QBert
	scene2.Add(g_QBertGO);

	// Level Section Observer
	sectionObserverGO = std::make_shared<dae::GameObject>();
	sectionObserverGO->AddComponent(new LevelSectionObserver(sectionObserverGO, g_QBertGO->GetComponent<dae::QBert>(), pyramid));
	scene2.Add(sectionObserverGO);

	// Transfer Game Observer
	//scene2.Add(g_GameObserverGO);


	//////////////////////////


	//// Section 03

	// Create Scene
	auto& scene3 = dae::SceneManager::GetInstance().CreateScene("Level02C");

	// Level Map
	pyramid = new Pyramid(300.f, 80.f, g_NrRows, g_CubesActualWidth, g_CubesActualHeight,
		0, 2, g_CubesSpriteWidth, g_CubesSpriteHeight);
	for (const std::shared_ptr<dae::GameObject>& cube : pyramid->m_CubeGOVector)
		scene3.Add(cube);

	// Transfer QBert
	scene3.Add(g_QBertGO);

	// Level Section Observer
	sectionObserverGO = std::make_shared<dae::GameObject>();
	sectionObserverGO->AddComponent(new LevelSectionObserver(sectionObserverGO, g_QBertGO->GetComponent<dae::QBert>(), pyramid));
	scene3.Add(sectionObserverGO);

	// Transfer Game Observer
	//scene3.Add(g_GameObserverGO);


	//////////////////////////


	//// Section 04

	// Create Scene
	auto& scene4 = dae::SceneManager::GetInstance().CreateScene("Level02D");

	// Level Map
	pyramid = new Pyramid(300.f, 80.f, g_NrRows, g_CubesActualWidth, g_CubesActualHeight,
		4, 2, g_CubesSpriteWidth, g_CubesSpriteHeight);
	for (const std::shared_ptr<dae::GameObject>& cube : pyramid->m_CubeGOVector)
		scene4.Add(cube);

	// Transfer QBert
	scene4.Add(g_QBertGO);

	// Level Section Observer
	sectionObserverGO = std::make_shared<dae::GameObject>();
	sectionObserverGO->AddComponent(new LevelSectionObserver(sectionObserverGO, g_QBertGO->GetComponent<dae::QBert>(), pyramid));
	scene4.Add(sectionObserverGO);

	// Transfer Game Observer
	//scene4.Add(g_GameObserverGO);
}

void LoadLevel03()
{
	//// Section 01

	// Create Scene
	auto& scene1 = dae::SceneManager::GetInstance().CreateScene("Level03A");

	// Level Map
	auto* pyramid = new Pyramid(300.f, 80.f, g_NrRows, g_CubesActualWidth, g_CubesActualHeight,
		5, 3, g_CubesSpriteWidth, g_CubesSpriteHeight);
	for (const std::shared_ptr<dae::GameObject>& cube : pyramid->m_CubeGOVector)
		scene1.Add(cube);

	// Transfer QBert
	scene1.Add(g_QBertGO);

	// Level Section Observer
	auto sectionObserverGO = std::make_shared<dae::GameObject>();
	sectionObserverGO->AddComponent(new LevelSectionObserver(sectionObserverGO, g_QBertGO->GetComponent<dae::QBert>(), pyramid));
	scene1.Add(sectionObserverGO);

	// Transfer Game Observer
	//scene1.Add(g_GameObserverGO);


	//////////////////////////


	//// Section 02

	// Create Scene
	auto& scene2 = dae::SceneManager::GetInstance().CreateScene("Level02B");

	// Level Map
	pyramid = new Pyramid(300.f, 80.f, g_NrRows, g_CubesActualWidth, g_CubesActualHeight,
		2, 3, g_CubesSpriteWidth, g_CubesSpriteHeight);
	for (const std::shared_ptr<dae::GameObject>& cube : pyramid->m_CubeGOVector)
		scene2.Add(cube);

	// Transfer QBert
	scene2.Add(g_QBertGO);

	// Level Section Observer
	sectionObserverGO = std::make_shared<dae::GameObject>();
	sectionObserverGO->AddComponent(new LevelSectionObserver(sectionObserverGO, g_QBertGO->GetComponent<dae::QBert>(), pyramid));
	scene2.Add(sectionObserverGO);

	// Transfer Game Observer
	//scene2.Add(g_GameObserverGO);


	//////////////////////////


	//// Section 03

	// Create Scene
	auto& scene3 = dae::SceneManager::GetInstance().CreateScene("Level02C");

	// Level Map
	pyramid = new Pyramid(300.f, 80.f, g_NrRows, g_CubesActualWidth, g_CubesActualHeight,
		1, 3, g_CubesSpriteWidth, g_CubesSpriteHeight);
	for (const std::shared_ptr<dae::GameObject>& cube : pyramid->m_CubeGOVector)
		scene3.Add(cube);

	// Transfer QBert
	scene3.Add(g_QBertGO);

	// Level Section Observer
	sectionObserverGO = std::make_shared<dae::GameObject>();
	sectionObserverGO->AddComponent(new LevelSectionObserver(sectionObserverGO, g_QBertGO->GetComponent<dae::QBert>(), pyramid));
	scene3.Add(sectionObserverGO);

	// Transfer Game Observer
	//scene3.Add(g_GameObserverGO);


	//////////////////////////


	//// Section 04

	// Create Scene
	auto& scene4 = dae::SceneManager::GetInstance().CreateScene("Level02D");

	// Level Map
	pyramid = new Pyramid(300.f, 80.f, g_NrRows, g_CubesActualWidth, g_CubesActualHeight,
		0, 3, g_CubesSpriteWidth, g_CubesSpriteHeight);
	for (const std::shared_ptr<dae::GameObject>& cube : pyramid->m_CubeGOVector)
		scene4.Add(cube);

	// Transfer QBert
	scene4.Add(g_QBertGO);

	// Level Section Observer
	sectionObserverGO = std::make_shared<dae::GameObject>();
	sectionObserverGO->AddComponent(new LevelSectionObserver(sectionObserverGO, g_QBertGO->GetComponent<dae::QBert>(), pyramid));
	scene4.Add(sectionObserverGO);

	// Transfer Game Observer
	//scene4.Add(g_GameObserverGO);
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

void SetUpGlobalGOs()
{
	// QBert
	const auto qBertSpriteWidth = 17.f;
	const auto qBertSpriteHeight = 16.f;
	auto qBertGO = std::make_shared<dae::GameObject>();
	qBertGO->AddComponent(new dae::QBert(qBertGO, g_NrRows, g_CubesActualWidth, g_CubesActualHeight, qBertSpriteWidth, qBertSpriteHeight));
	qBertGO->AddComponent(new dae::GraphicsComponent("QBert Sprites.png", 304, 50, 49, 48, qBertSpriteWidth * 2, 0, qBertSpriteWidth, qBertSpriteHeight));
	
	 
	// Player Input
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

	
	g_QBertGO = std::move(qBertGO);


	// Game Observer
	//auto gameObjectGO = std::make_shared<dae::GameObject>();
	//g_GameObserverGO = std::move(gameObjectGO);
}

void PrintInstructions()
{
	std::cout << "Controls:\n";
	std::cout << "\n";
	std::cout << "   W   | Move Up/Right\n";
	std::cout << "   S   | Move Down/Left\n";
	std::cout << "   A   | Move Up/Left\n";
	std::cout << "   D   | Move Down/Right\n\n";
}