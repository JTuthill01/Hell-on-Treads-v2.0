#pragma once

namespace Particle
{
	class Particle
	{
	public:
		Particle(sf::Texture* texture, sf::Vector2f position, sf::Vector2f scale, sf::Vector2f direction, thor::Timer timer);
		~Particle();

		void render(sf::RenderTarget& target);
		void update(const float& deltaTime);

	private:
		sf::Texture* mParticleTexture;
		sf::Sprite mParticleSprite;
		sf::Vector2f mParticlePosition;
		sf::Vector2f mParticleScale;
		sf::Vector2f mParticleDirection;

		thor::Timer mParticleTimer;
	};
}