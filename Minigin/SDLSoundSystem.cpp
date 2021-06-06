#include "MiniginPCH.h"
#include "SDLSoundSystem.h"

SDLSoundSystem::SDLSoundSystem()
{
	m_Playing.store(true);
	m_SoundThread = std::thread([this]() {this->Update(); });
}

SDLSoundSystem::~SDLSoundSystem()
{
	m_Playing.store(false);
	m_QueueActive.notify_one();
	m_SoundThread.join();
}

void SDLSoundSystem::Play(const std::string& filename, const float volume)
{
	std::lock_guard<std::mutex> mutexLock{ m_Mutex };
	m_SoundQueue.push(SoundRequest{ filename, volume });
	m_QueueActive.notify_one();
}

void SDLSoundSystem::InvertMute()
{
	m_Muted = !m_Muted;
}

void SDLSoundSystem::Update()
{
	while(m_Playing.load())
	{
		while(!m_SoundQueue.empty())
		{
			std::unique_lock<std::mutex> mutexLock{ m_Mutex };
			SoundRequest sound = m_SoundQueue.front();
			m_SoundQueue.pop();
			if (!m_Muted)
			{
				auto it = m_LoadedSounds.find(sound.filename);
				if(it == m_LoadedSounds.end())
				{
					LoadSound(sound.filename);
					it = m_LoadedSounds.find(sound.filename);
				}
				
				playSoundFromMemory(it->second->GetAudio(), int(SDL_MIX_MAXVOLUME * sound.volume));
			}
		}

		std::unique_lock<std::mutex> guard{ m_Mutex };
		m_QueueActive.wait(guard);
	}
}

void SDLSoundSystem::LoadSound(std::string filename)
{
	if (m_LoadedSounds.find(filename) == m_LoadedSounds.end())
	{
		auto newWrappedAudio = new WrappedAudio(createAudio(filename.c_str(), false, 1));
		m_LoadedSounds.emplace(filename, newWrappedAudio);
		//std::cout << "Sound file \"" << filename << "\" loaded\n";
	}
	//else
		//std::cout << "The sound file \"" << filename << "\" has already been loaded\n";
}