#include "pch.hpp"
#include "Audio.hpp"

Audio::Audio() : mVolume(20.F)
{
}

Audio::~Audio()
{
}

void Audio::loadSound(const std::string& filePath)
{
	if (!mBuffer.loadFromFile(filePath))
		std::cerr << "Fucking sound file didn't fucking load!!!" << filePath <<"\n";

	mSound.setBuffer(mBuffer);
}

void Audio::play() { mSound.play(); }

void Audio::stop() { mSound.stop(); }

void Audio::setVolume(float volume)
{
	mVolume = volume;
	mSound.setVolume(mVolume);
}