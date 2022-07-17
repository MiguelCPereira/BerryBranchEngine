#include "MiniginPCH.h"
#include "SoundServiceLocator.h"
#include "SoundSystem.h"

NullSoundSystem SoundServiceLocator::m_DefaultSoundSys;
SoundSystem* SoundServiceLocator::m_SoundSysInstance = &m_DefaultSoundSys;

void SoundServiceLocator::RegisterSoundSystem(SoundSystem* soundSys)
{
	m_SoundSysInstance = soundSys == nullptr ? &m_DefaultSoundSys : soundSys;
}
