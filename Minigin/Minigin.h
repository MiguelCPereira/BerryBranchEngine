#pragma once
#include "MiniginLibType.h"


struct SDL_Window;
namespace dae
{
	class MINIGIN_ENTRY Minigin
	{
	public:
		void Initialize();
		void LoadDemo() const;
		void Cleanup();
		void Run();
	private:
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* m_Window{};
	};
}