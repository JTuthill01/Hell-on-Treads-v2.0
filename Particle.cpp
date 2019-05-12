#include "pch.hpp"
#include "Particle.hpp"

namespace Particle
{
	Particle::Particle(sf::Texture* texture, sf::Vector2f position, sf::Vector2f scale, sf::Vector2f direction, thor::Timer timer) : mParticleTexture(texture), mParticlePosition(position), mParticleDirection(direction),
		mParticleTimer(timer), mParticleScale(scale)
	{
		this->mParticleSprite.setTexture(*this->mParticleTexture);
		this->mParticleSprite.setPosition(position);
		this->mParticleSprite.setScale(scale);
		this->mParticleSprite.setRotation(atan2(this->mParticleDirection.y, this->mParticleDirection.x) * 180 / thor::Pi + 180);
	}

	Particle::~Particle() = default;

	void Particle::render(sf::RenderTarget & target)
	{
		if (!this->mParticleTimer.isExpired())
			target.draw(this->mParticleSprite);
	}

	void Particle::update(const float& deltaTime) { this->mParticleSprite.move(8.F * deltaTime * 62.5F, 4.F * deltaTime * 62.5F); }
}