#include "stdafx.hpp"
#include "Upgrades.hpp"

namespace upgrades
{
	Upgrades::Upgrades(std::vector<sf::Texture>& textures, sf::Vector2f position, int type, thor::Timer isAlive)
	{
		this->mUpgradeTextures = &textures;

		this->mPosition = position;

		this->mIsAliveTimer = isAlive;

		this->mType = type;

		if (this->mType < (*this->mUpgradeTextures).size())
			this->mUpgradeSprite.setTexture((*this->mUpgradeTextures)[this->mType]);

		else
			std::cerr << "NO fucking texture was found" << "\n";

		this->mUpgradeSprite.setPosition(position);
	}

	Upgrades::~Upgrades() = default;

	void Upgrades::render(sf::RenderTarget& target){ target.draw(this->mUpgradeSprite); }

	void Upgrades::timer() { this->mIsAliveTimer.restart(sf::seconds(0.5F)); }
}