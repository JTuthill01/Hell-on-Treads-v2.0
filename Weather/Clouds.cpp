#include "pch.hpp"
#include "Clouds.hpp"

Clouds::Clouds(std::vector<sf::Texture>& texture, sf::Vector2f position)
{
	mClouds = &texture;
	mCloudPosition = position;

	mCloudSprite.setTexture((*mClouds)[0]);
	mCloudSprite.setPosition(position);
	mCloudSprite.setColor(sf::Color(184, 134, 11, 255));
}

Clouds::~Clouds()
{
}

void Clouds::render(sf::RenderTarget& target)
{
	target.draw(mCloudSprite);
}

void Clouds::update(const float& deltaTime)
{
	mCloudSprite.move(0.5F, 0.F);
}
