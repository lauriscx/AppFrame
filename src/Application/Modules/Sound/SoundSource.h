#pragma once
#include "Core/Core.h"

namespace AppFrame {
	class SoundSource {
	public:
		SoundSource();


		void SetPitch(float pitch);
		void SetGain(float gain);
		void SetLoop(bool loop);
		void SetPosition(float x, float y, float z);
		void SetVelocity(float x, float y, float z);

		void SetSound(unsigned int sound);

		void Play();

		~SoundSource();
	private:
		unsigned int m_Source;

		unsigned int m_Sound;

		unsigned int m_Pitch;
		unsigned int m_Gain;
		float m_Position[3];
		float m_Velocity[3];
		unsigned int m_Loop;
	};
}