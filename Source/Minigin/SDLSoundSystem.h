#pragma once
#include "SoundSystem.h"
#include <mutex>
#include <queue>
#include <unordered_map>
#include "WrappedAudio.h"

class SDLSoundSystem final : public SoundSystem
{
public:
	SDLSoundSystem();
	~SDLSoundSystem() override;

	SDLSoundSystem(const SDLSoundSystem&) = delete;
	SDLSoundSystem& operator=(const SDLSoundSystem&) = delete;
	SDLSoundSystem(SDLSoundSystem&&) = delete;
	SDLSoundSystem& operator=(SDLSoundSystem&&) = delete;
	
	void Play(const std::string& filename, const float volume = 1.f) override;
	void InvertMute() override;

private:
	struct SoundRequest
	{
		const std::string filename;
		const float volume;
	};
	
	void Update();
	void LoadSound(std::string filename);

	bool m_Muted{};
	std::thread m_SoundThread;
	std::queue<SoundRequest> m_SoundQueue{};
	std::condition_variable m_QueueActive{};
	std::mutex m_Mutex;
	std::atomic<bool> m_Playing;

	std::unordered_map<std::string, WrappedAudio*> m_LoadedSounds;
};

