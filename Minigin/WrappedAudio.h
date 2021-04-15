#pragma once
#include "audio.h"

class WrappedAudio
{
public:
	Audio* GetAudio() const { return m_Audio; };
	WrappedAudio(Audio* audio) : m_Audio{ audio } {}
	~WrappedAudio() { delete m_Audio; }

	WrappedAudio(const WrappedAudio&) = delete;
	WrappedAudio& operator=(const WrappedAudio&) = delete;
	WrappedAudio(WrappedAudio&&) = delete;
	WrappedAudio& operator=(WrappedAudio&&) = delete;

private:
	Audio* m_Audio;
};

