#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "GameObject.h"
#include "Scene.h"

#include "FPSComponent.h"
#include "GraphicsComponent.h"
#include "HPDisplay.h"
#include "LifeComponent.h"
#include "TextComponent.h"


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
	gameObject->AddComponent(new TextComponent("00 FPS", font, 255,255,0));
	gameObject->GetComponent<TextComponent>()->SetPosition(5, 5);
	scene.Add(gameObject);

	// QBert
	gameObject = std::make_shared<GameObject>();
	gameObject->AddComponent(new GraphicsComponent("qBert.png", 250, 270));
	gameObject->AddComponent(new LifeComponent(3));
	scene.Add(gameObject);

	// HP Display
	gameObject->GetComponent<LifeComponent>()->GetSubject()->AddObserver(make_shared<HPDisplay>(gameObject->GetComponent<TextComponent>()));
	int startingHP = gameObject->GetComponent<LifeComponent>()->GetHP();
	std::string string = "Remaining Lives: ";
	string.append(std::to_string(startingHP));
	gameObject = std::make_shared<GameObject>();
	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 25);
	gameObject->AddComponent(new TextComponent(string, font));
	gameObject->GetComponent<TextComponent>()->SetPosition(215, 140);
	scene.Add(gameObject);

	// Input
	auto dieKeyboard = std::make_unique<DieCommand>();
	dieKeyboard->SetActor(gameObject);
	dieKeyboard->SetButtonPressType(ButtonPress::PressedDown);
	InputManager::GetInstance().AddCommand(SDLK_SPACE, std::move(dieKeyboard));

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
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

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
