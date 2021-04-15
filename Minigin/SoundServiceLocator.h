#pragma once

class SoundSystem;
class NullSoundSystem;

class SoundServiceLocator final
{
public:
	static SoundSystem& GetSoundSystem() { return *m_SoundSysInstance; }
	static void RegisterSoundSystem(SoundSystem* soundSys);
private:
	static SoundSystem* m_SoundSysInstance;
	static NullSoundSystem m_DefaultSoundSys;
};