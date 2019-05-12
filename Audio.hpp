#pragma once
class Audio
{
public:
	Audio();
	~Audio();

	void loadSound(const std::string& filePath);
	void play();
	void stop();
	void setVolume(float volume);

	void setLoop(bool t_f) { mSound.setLoop(t_f); }

private:
	sf::Sound mSound;
	sf::SoundBuffer mBuffer;

	float mVolume;
};