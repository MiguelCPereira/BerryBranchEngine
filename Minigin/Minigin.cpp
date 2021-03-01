#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "TextObject.h"
#include "GameObject.h"
#include "Scene.h"
#include "FPSComponent.h"
#include "HPTextComponent.h"
#include "LifeComponent.h"

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

	auto go = std::make_shared<GameObject>();
	go->SetTexture("background.jpg");
	scene.Add(go);

	go = std::make_shared<GameObject>();
	go->SetTexture("logo.png");
	go->SetPosition(216, 180);
	scene.Add(go);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_shared<TextObject>("Programming 4 Assignment", font);
	to->SetPosition(80, 20);
	scene.Add(to);

	auto* FPSComp = new dae::FPSComponent;
	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 19);
	to = std::make_shared<TextObject>("00 FPS", font, FPSComp);
	to->SetPosition(5, 5);
	scene.Add(to);
	
	go = std::make_shared<GameObject>();
	go->SetTexture("qBert.png");
	go->SetPosition(250, 270);
	//auto* qBertComp = new QBertLifeComponent(); // I don't understand why this leads to errors
	//go->AddComponent(qBertComp);
	auto dieKeyboard = std::make_unique<DieCommand>();
	dieKeyboard->SetActor(go);
	dieKeyboard->SetButtonPressType(ButtonPress::PressedDown);
	InputManager::GetInstance().AddCommand(SDLK_SPACE, std::move(dieKeyboard));
	scene.Add(go);

	auto* HPTextComp = new dae::HPTextComponent;
	to = std::make_shared<TextObject>("Remaining Lives: 0", font, HPTextComp);
	to->SetPosition(238, 140);
	scene.Add(to);

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
