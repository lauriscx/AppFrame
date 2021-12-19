#include "SoundSource.h"

SoundSource::SoundSource() {
	m_Pitch = 1;
	m_Gain	= 1;
	m_Loop	= false;
	m_Sound = 0;

	m_Position[0] = 0;
	m_Position[1] = 0;
	m_Position[2] = 0;
	m_Velocity[0] = 0;
	m_Velocity[1] = 0;
	m_Velocity[2] = 0;

	alGenSources(1, &m_Source);

	alSourcef(m_Source, AL_PITCH	, m_Pitch);
	alSourcef(m_Source, AL_GAIN		, m_Gain);
	alSourcei(m_Source, AL_LOOPING	, m_Loop);
	alSourcei(m_Source, AL_BUFFER	, m_Sound);

	alSource3f(m_Source, AL_POSITION, m_Position[0], m_Position[1], m_Position[2]);
	alSource3f(m_Source, AL_VELOCITY, m_Velocity[0], m_Velocity[1], m_Velocity[2]);
}

void SoundSource::SetSound(unsigned int sound) {
	m_Sound = sound;
	alSourcei(m_Source, AL_BUFFER, m_Sound);
}

void SoundSource::SetPitch(float pitch) {
	m_Pitch = pitch;
	alSourcef(m_Source, AL_PITCH, m_Pitch);
}

void SoundSource::SetGain(float gain) {
	m_Gain = gain;
	alSourcef(m_Source, AL_GAIN, m_Gain);
}

void SoundSource::SetPosition(float x, float y, float z) {
	m_Position[0] = x;
	m_Position[1] = y;
	m_Position[2] = z;
	alSource3f(m_Source, AL_POSITION, m_Position[0], m_Position[1], m_Position[2]);
}

void SoundSource::SetVelocity(float x, float y, float z) {
	m_Velocity[0] = x;
	m_Velocity[1] = y;
	m_Velocity[2] = z;
	alSource3f(m_Source, AL_VELOCITY, m_Velocity[0], m_Velocity[1], m_Velocity[2]);
}

void SoundSource::SetLoop(bool loop) {
	m_Loop = loop;
	alSourcei(m_Source, AL_LOOPING, (int)m_Loop);
}

void SoundSource::Play() {
	if (m_Sound != 0) {
		alSourcePlay(m_Source);
	}
}

SoundSource::~SoundSource() {
	alDeleteSources(1, &m_Source);
}