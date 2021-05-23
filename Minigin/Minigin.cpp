#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>

#include "audio.h"
#include "GameObject.h"
#include "Scene.h"

#include "FPSComponent.h"
#include "GraphicsComponent.h"
#include "LivesDisplayComponent.h"
#include "PointsDisplayComponent.h"
#include "QBertComponent.h"
#include "SDLSoundSystem.h"
#include "TextComponent.h"

#include "SoundServiceLocator.h"
#include "LoggingSoundSystem.h"


using namespace std;
using namespace std::chrono;

void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);

	// Initialize SDL
	_putenv("SDL_AUDIODRIVER=DirectSound");
	SDL_Init(SDL_INIT_AUDIO);
	initAudio();

	// Initialize Sound System
	const auto soundSystem = new SDLSoundSystem();
	const auto loggingSystem = new LoggingSoundSystem(soundSystem);
	SoundServiceLocator::RegisterSoundSystem(loggingSystem);

	// Tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const 
{

	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	// DAE Background
	auto gameObject = std::make_shared<GameObject>();
	gameObject->AddComponent(new GraphicsComponent("background.jpg"));
	scene.Add(gameObject);

	
	// DAE Logo
	gameObject = std::make_shared<GameObject>();
	gameObject->AddComponent(new GraphicsComponent("logo.png", 216, 180));
	scene.Add(gameObject);

	
	// Engine Title
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	gameObject = std::make_shared<GameObject>();
	gameObject->AddComponent(new TextComponent("Programming 4 Assignment", font));
	gameObject->GetComponent<TextComponent>()->SetPosition(80, 20);
	scene.Add(gameObject);

	
	// FPS Counter
	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 19);
	gameObject = std::make_shared<GameObject>();
	gameObject->AddComponent(new FPSComponent(gameObject));
	gameObject->AddComponent(new TextComponent("FAIL FPS", font, 255,255,0));
	gameObject->GetComponent<TextComponent>()->SetPosition(5, 5);
	scene.Add(gameObject);


	// QBert
	auto qBertGameObject = std::make_shared<GameObject>();
	qBertGameObject->AddComponent(new QBertComponent(qBertGameObject));
	qBertGameObject->AddComponent(new GraphicsComponent("qBert.png", 50, 270));
	scene.Add(qBertGameObject);
	
	
	// Input
	auto dieKeyboard = std::make_unique<DieCommand>();
	dieKeyboard->SetActor(qBertGameObject);
	dieKeyboard->SetButtonPressType(ButtonPress::PressedDown);
	InputManager::GetInstance().AddCommand(SDLK_q, std::move(dieKeyboard));

	auto colorChangeKeyboard = std::make_unique<ColorChangeCommand>();
	colorChangeKeyboard->SetActor(qBertGameObject);
	colorChangeKeyboard->SetButtonPressType(ButtonPress::PressedDown);
	InputManager::GetInstance().AddCommand(SDLK_w, std::move(colorChangeKeyboard));

	auto tileChangeKeyboard = std::make_unique<TileChangeCommand>();
	tileChangeKeyboard->SetActor(qBertGameObject);
	tileChangeKeyboard->SetButtonPressType(ButtonPress::PressedDown);
	InputManager::GetInstance().AddCommand(SDLK_e, std::move(tileChangeKeyboard));

	auto playSoundKeyboard = std::make_unique<PlaySoundCommand>(&SoundServiceLocator::GetSoundSystem());
	playSoundKeyboard->SetActor(qBertGameObject);
	playSoundKeyboard->SetButtonPressType(ButtonPress::PressedDown);
	InputManager::GetInstance().AddCommand(SDLK_SPACE, std::move(playSoundKeyboard));

	
	// Lives Displays
	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 25);
	gameObject = std::make_shared<GameObject>();
	gameObject->AddComponent(new TextComponent("Remaining Lives: FAIL", font));
	gameObject->GetComponent<TextComponent>()->SetPosition(13, 140);
	gameObject->AddComponent(new LivesDisplayComponent(gameObject, qBertGameObject->GetComponent<QBertComponent>()));
	scene.Add(gameObject);

	
	// Points Displays
	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 25);
	gameObject = std::make_shared<GameObject>();
	gameObject->AddComponent(new TextComponent("Points: FAIL", font));
	gameObject->GetComponent<TextComponent>()->SetPosition(70, 180);
	gameObject->AddComponent(new PointsDisplayComponent(gameObject, qBertGameObject->GetComponent<QBertComponent>()));
	scene.Add(gameObject);

	
	// 2nd QBert
	auto qBertGameObject2 = std::make_shared<GameObject>();
	qBertGameObject2->AddComponent(new QBertComponent(qBertGameObject2));
	qBertGameObject2->AddComponent(new GraphicsComponent("qBert.png", 445, 270));
	scene.Add(qBertGameObject2);
	
	auto dieKeyboard2 = std::make_unique<DieCommand>();
	dieKeyboard2->SetActor(qBertGameObject2);
	dieKeyboard2->SetButtonPressType(ButtonPress::PressedDown);
	InputManager::GetInstance().AddCommand(SDLK_i, std::move(dieKeyboard2));
	auto colorChangeKeyboard2 = std::make_unique<ColorChangeCommand>();
	colorChangeKeyboard2->SetActor(qBertGameObject2);
	colorChangeKeyboard2->SetButtonPressType(ButtonPress::PressedDown);
	InputManager::GetInstance().AddCommand(SDLK_o, std::move(colorChangeKeyboard2));
	auto tileChangeKeyboard2 = std::make_unique<TileChangeCommand>();
	tileChangeKeyboard2->SetActor(qBertGameObject2);
	tileChangeKeyboard2->SetButtonPressType(ButtonPress::PressedDown);
	InputManager::GetInstance().AddCommand(SDLK_p, std::move(tileChangeKeyboard2));

	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 25);
	gameObject = std::make_shared<GameObject>();
	gameObject->AddComponent(new TextComponent("Remaining Lives: FAIL", font));
	gameObject->GetComponent<TextComponent>()->SetPosition(408, 140);
	gameObject->AddComponent(new LivesDisplayComponent(gameObject, qBertGameObject2->GetComponent<QBertComponent>()));
	scene.Add(gameObject);

	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 25);
	gameObject = std::make_shared<GameObject>();
	gameObject->AddComponent(new TextComponent("Points: FAIL", font));
	gameObject->GetComponent<TextComponent>()->SetPosition(465, 180);
	gameObject->AddComponent(new PointsDisplayComponent(gameObject, qBertGameObject2->GetComponent<QBertComponent>()));
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

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		bool doContinue = true;
		auto lastTime = std::chrono::high_resolution_clock::now();

		while (doContinue)
		{
			const auto currentTime = high_resolution_clock::now();
			const float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
			doContinue = input.ProcessInput();
			sceneManager.Update(deltaTime);
			renderer.Render();
			lastTime = currentTime;
		}

		// Scrapped Fixed Update Method (optimal in case of networking)
		// 
		//float lag = 0.0f;
		//while (doContinue)
		//{
		//	const auto currentTime = high_resolution_clock::now();
		//	const float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
		//	lastTime = currentTime;
		//	lag += deltaTime;
			
		//	doContinue = input.ProcessInput();

		//	while(lag >= MsPerFrame)
		//	{
		//		sceneManager.Update(MsPerFrame / 1000.f);
		//		lag -= MsPerFrame;
		//	}
			
		//	renderer.Render();
		//}
	}

	Cleanup();
}
