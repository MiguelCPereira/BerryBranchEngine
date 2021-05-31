#pragma once
#include "MiniginLibType.h"

class SoundSystem;
class NullSoundSystem;

class SoundServiceLocator final
{
public:
	static MINIGIN_ENTRY SoundSystem & GetSoundSystem() { return *m_SoundSysInstance; }
	static void RegisterSoundSystem(SoundSystem* soundSys);
private:
	static SoundSystem* m_SoundSysInstance;
	static NullSoundSystem m_DefaultSoundSys;
};