#include "pch.hpp"
#include "Weather.hpp"
#include <random>

Weather::Weather() 
{
	if (!mTexture.loadFromFile("Resources/Textures/Weather/drop1.png"))
		std::cerr << "Rain failed to load" << "\n";

	mEmitter.setEmissionRate(150.F);
	mEmitter.setParticleLifetime(sf::seconds(5.F));
	mEmitter.setParticlePosition(thor::Distributions::deflect(sf::Vector2f(100.F, 10.F), 100.F));
	mEmitter.setParticleVelocity(thor::Distributions::deflect(sf::Vector2f(500.F, 10.F), 80.F));

	mSystem.setTexture(mTexture);
	mSystem.addEmitter(mEmitter);
	
	thor::FadeAnimation mFader(0.15F, 0.15F);

	mSystem.addAffector(thor::AnimationAffector(mFader));
	mSystem.addAffector(thor::TorqueAffector(100.F));
	mSystem.addAffector(thor::ForceAffector(sf::Vector2f(0.F, 100.F)));

	mAudio.loadSound("Resources/Sounds/Weather/rain_thunder.wav");
	mAudio.setLoop(true);
	mAudio.setVolume(40.F);
	mAudio.play();
}

Weather::Weather(const Weather& other)
{
	//Particles
	this->mTexture = other.mTexture;
	this->mWindow = other.mWindow;
	this->mTime = other.mTime;
	this->mClock = other.mClock;

	//Thor stuff
	this->mGradient = other.mGradient;
	this->mEmitter = other.mEmitter;
}


Weather::~Weather()
{
}

void Weather::createSnow()
{
	if (!mTexture.loadFromFile("Resources/Textures/Weather/snow.png"))
		std::cerr << "Snow failed to load" << "\n";

	mEmitter.setEmissionRate(150.F);
	mEmitter.setParticleLifetime(sf::seconds(5.F));
	mEmitter.setParticlePosition(thor::Distributions::deflect(sf::Vector2f(100.F, 10.F), 100.F));
	mEmitter.setParticleVelocity(thor::Distributions::deflect(sf::Vector2f(500.F, 10.F), 80.F));

	mSystem.setTexture(mTexture);
	mSystem.addEmitter(mEmitter);

	thor::FadeAnimation mFader(0.15F, 0.15F);

	mSystem.addAffector(thor::AnimationAffector(mFader));
	mSystem.addAffector(thor::TorqueAffector(100.F));
	mSystem.addAffector(thor::ForceAffector(sf::Vector2f(0.F, 100.F)));
}

void Weather::renderSnow(sf::RenderTarget& target)
{
	target.draw(mSystem, sf::BlendAdd);
}

void Weather::render(sf::RenderTarget& target)
{
	target.draw(mSystem, sf::BlendAdd);
}

void Weather::updateSnow()
{
	mTime = mClock.restart();

	mSystem.update(mTime);
}

void Weather::update()
{
	mTime = mClock.restart();

	mSystem.update(mTime);
}

void Weather::stopAudio() { mAudio.stop(); }
