#include "ResourceSound.h"
#include <al.h>
#include "FileSystem/VFS/VFS.h"
#include "FileSystem/File.h"
#include <stdio.h>

ResourceSound::ResourceSound() {}

unsigned int ResourceSound::Get() {
	return m_ResourceHandle;
}

bool ResourceSound::IsAvailable() {
	return m_ResourceHandle;
}

bool ResourceSound::Load(std::filesystem::path file) {
	File* _file = Engine::VFS::GetInstance()->ReadFile(file);
	/*if (_file && _file->IsDataAvailable()) {
		//Copy data to WAV header from file.
		WAV_HEADER Header;
		memcpy(&Header, _file->GetData(), sizeof(WAV_HEADER));

	//	alGenBuffers(1, &m_ResourceHandle);

//		alBufferData(SoundBufferHandle, format, mmeBuffer, num_bytes, sampleRate);
		//delete memBuffer

		//close file.

		delete _file;//It will erease all allocated memory inside(mean data which is char*).
		
		ALenum err = alGetError();
		if (err != AL_NO_ERROR)
		{
			fprintf(stderr, "OpenAL Error: %s\n", alGetString(err));
			if (m_ResourceHandle && alIsBuffer(m_ResourceHandle))
				alDeleteBuffers(1, &m_ResourceHandle);
			return false;
		}
		return true;
	}*/
	alGenBuffers(1, &m_ResourceHandle);
	/* Fill buffer with Sine-Wave */
	float freq = 440.f;
	int seconds = 4;
	unsigned sample_rate = 22050;
	size_t buf_size = seconds * sample_rate;

	char *samples;
	samples = new char[buf_size];
	for (int i = 0; i < buf_size; ++i) {
		samples[i] = 32760 * sin((2.f*float(3.14)*freq) / sample_rate * i);
	}

	/* Download buffer to OpenAL */
	alBufferData(m_ResourceHandle, AL_FORMAT_MONO16, samples, buf_size, sample_rate);
	return true;
}

size_t ResourceSound::GetMemoryUsage() {
	return size_t();
}

ResourceSound::~ResourceSound() {
	//alDeleteBuffers(1, &m_ResourceHandle);
	//m_ResourceHandle = 0;
}


/*
std::int32_t convert_to_int(char* buffer, std::size_t len)
{
	std::int32_t a = 0;
	if(std::endian::native == std::endian::little)
		std::memcpy(&a, buffer, len);
	else
		for(std::size_t i = 0; i < len; ++i)
			reinterpret_cast<char*>(&a)[3 - i] = buffer[i];
	return a;
}

bool load_wav_file_header(std::ifstream& file,
						  std::uint8_t& channels,
						  std::int32_t& sampleRate,
						  std::uint8_t& bitsPerSample,
						  ALsizei& size)
{
	char buffer[4];
	if(!file.is_open())
		return false;

	// the RIFF
	if(!file.read(buffer, 4))
	{
		std::cerr << "ERROR: could not read RIFF" << std::endl;
		return false;
	}
	if(std::strncmp(buffer, "RIFF", 4) != 0)
	{
		std::cerr << "ERROR: file is not a valid WAVE file (header doesn't begin with RIFF)" << std::endl;
		return false;
	}

	// the size of the file
	if(!file.read(buffer, 4))
	{
		std::cerr << "ERROR: could not read size of file" << std::endl;
		return false;
	}

	// the WAVE
	if(!file.read(buffer, 4))
	{
		std::cerr << "ERROR: could not read WAVE" << std::endl;
		return false;
	}
	if(std::strncmp(buffer, "WAVE", 4) != 0)
	{
		std::cerr << "ERROR: file is not a valid WAVE file (header doesn't contain WAVE)" << std::endl;
		return false;
	}

	// "fmt/0"
	if(!file.read(buffer, 4))
	{
		std::cerr << "ERROR: could not read fmt/0" << std::endl;
		return false;
	}

	// this is always 16, the size of the fmt data chunk
	if(!file.read(buffer, 4))
	{
		std::cerr << "ERROR: could not read the 16" << std::endl;
		return false;
	}

	// PCM should be 1?
	if(!file.read(buffer, 2))
	{
		std::cerr << "ERROR: could not read PCM" << std::endl;
		return false;
	}

	// the number of channels
	if(!file.read(buffer, 2))
	{
		std::cerr << "ERROR: could not read number of channels" << std::endl;
		return false;
	}
	channels = convert_to_int(buffer, 2);

	// sample rate
	if(!file.read(buffer, 4))
	{
		std::cerr << "ERROR: could not read sample rate" << std::endl;
		return false;
	}
	sampleRate = convert_to_int(buffer, 4);

	// (sampleRate * bitsPerSample * channels) / 8
	if(!file.read(buffer, 4))
	{
		std::cerr << "ERROR: could not read (sampleRate * bitsPerSample * channels) / 8" << std::endl;
		return false;
	}

	// ?? dafaq
	if(!file.read(buffer, 2))
	{
		std::cerr << "ERROR: could not read dafaq" << std::endl;
		return false;
	}

	// bitsPerSample
	if(!file.read(buffer, 2))
	{
		std::cerr << "ERROR: could not read bits per sample" << std::endl;
		return false;
	}
	bitsPerSample = convert_to_int(buffer, 2);

	// data chunk header "data"
	if(!file.read(buffer, 4))
	{
		std::cerr << "ERROR: could not read data chunk header" << std::endl;
		return false;
	}
	if(std::strncmp(buffer, "data", 4) != 0)
	{
		std::cerr << "ERROR: file is not a valid WAVE file (doesn't have 'data' tag)" << std::endl;
		return false;
	}

	// size of data
	if(!file.read(buffer, 4))
	{
		std::cerr << "ERROR: could not read data size" << std::endl;
		return false;
	}
	size = convert_to_int(buffer, 4);

	// cannot be at the end of file 
if (file.eof())
{
	std::cerr << "ERROR: reached EOF on the file" << std::endl;
	return false;
}
if (file.fail())
{
	std::cerr << "ERROR: fail state set on the file" << std::endl;
	return false;
}

return true;
}

char* load_wav(const std::string& filename,
	std::uint8_t& channels,
	std::int32_t& sampleRate,
	std::uint8_t& bitsPerSample,
	ALsizei& size)
{
	std::ifstream in(filename, std::ios::binary);
	if (!in.is_open())
	{
		std::cerr << "ERROR: Could not open \"" << filename << "\"" << std::endl;
		return nullptr;
	}
	if (!load_wav_file_header(in, channels, sampleRate, bitsPerSample, size))
	{
		std::cerr << "ERROR: Could not load wav header of \"" << filename << "\"" << std::endl;
		return nullptr;
	}

	char* data = new char[size];

	in.read(data, size);

	return data;
}
*/