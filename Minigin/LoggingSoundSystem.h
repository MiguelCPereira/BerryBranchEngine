#pragma once
#include "SoundSystem.h"

class LoggingSoundSystem final : public SoundSystem
{
public:
	LoggingSoundSystem(SoundSystem* soundSys);
	~LoggingSoundSystem() override = default;
	
	void Play(const std::string& filename, const float volume = 1.f) override;

	void InvertMute() override {}

	LoggingSoundSystem() = default;
	LoggingSoundSystem(const LoggingSoundSystem&) = delete;
	LoggingSoundSystem& operator=(const LoggingSoundSystem&) = delete;
	LoggingSoundSystem(LoggingSoundSystem&&) = delete;
	LoggingSoundSystem& operator=(LoggingSoundSystem&&) = delete;

private:
	SoundSystem* m_SoundSystem{ nullptr };
};

