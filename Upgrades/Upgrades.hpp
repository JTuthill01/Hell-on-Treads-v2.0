#pragma once

namespace upgrades 
{
	class Upgrades
	{
	public:
		Upgrades(std::vector<sf::Texture>& textures, sf::Vector2f position, int type, thor::Timer isAlive);
		~Upgrades();

		void render(sf::RenderTarget& target);
		void timer();

	private:
		std::vector<sf::Texture>* mUpgradeTextures;
		sf::Sprite mUpgradeSprite;
		sf::Vector2f mPosition;
		thor::Timer mIsAliveTimer;

		int mType;
	};

}