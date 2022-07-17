#include "MiniginPCH.h"
#include "LoggingSoundSystem.h"

LoggingSoundSystem::LoggingSoundSystem(SoundSystem* soundSys)
	: m_SoundSystem{soundSys}
{
}

void LoggingSoundSystem::Play(const std::string& filename, const float volume)
{
	if (m_SoundSystem != nullptr)
	{
		std::cout << "Playing sound file from path \"" << filename << "\" at volume " << volume << '\n';
		m_SoundSystem->Play(filename, volume);
	}
}