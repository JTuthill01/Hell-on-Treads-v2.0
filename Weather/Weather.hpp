#pragma once
#include <Resources/Audio.hpp>

class Weather
{
public:
	Weather();
	Weather(const Weather& other);
	~Weather();

	void createSnow();
	void renderSnow(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
	void updateSnow();
	void update();
	void stopAudio();

private:
	//Particles
	sf::Texture mTexture;
	sf::RenderWindow* mWindow;
	sf::Time mTime;
	sf::Clock mClock;

	
	//Thor stuff
	thor::ColorGradient mGradient;
	thor::UniversalEmitter mEmitter;
	thor::ParticleSystem mSystem;

	//Audio
	Audio mAudio;
};

