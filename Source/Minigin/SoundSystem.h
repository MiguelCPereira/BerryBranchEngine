#pragma once

using sound_id = unsigned short;

class SoundSystem
{
public:
	virtual ~SoundSystem() = default;
	
	virtual void Play(const std::string& filename, const float volume = 1.f) = 0;
	virtual void InvertMute() = 0;

	SoundSystem() = default;
	SoundSystem(const SoundSystem&) = delete;
	SoundSystem& operator=(const SoundSystem&) = delete;
	SoundSystem(SoundSystem&&) = delete;
	SoundSystem& operator=(SoundSystem&&) = delete;
};

class NullSoundSystem final : public SoundSystem
{
public:
	~NullSoundSystem() override = default;
	
	void Play(const std::string&, const float = 1.f) override {}
	void InvertMute() override {}

	NullSoundSystem() = default;
	NullSoundSystem(const NullSoundSystem&) = delete;
	NullSoundSystem& operator=(const NullSoundSystem&) = delete;
	NullSoundSystem(NullSoundSystem&&) = delete;
	NullSoundSystem& operator=(NullSoundSystem&&) = delete;
};

