#pragma once
#include <Entity/Enemy/Enemy.hpp>
#include <Entity/Entity.hpp>
#include <Entity/Player/Player.hpp>
#include <Weather/Weather.hpp>

class Level
{
public:
	Level(sf::RenderWindow* window, std::vector<Level*> level);
	~Level();

	void update(const float& deltaTime);
	void render(sf::RenderTarget& target);

private:
	sf::Texture mTexture;
	sf::Sprite mSprite;
	sf::RenderWindow* mWindow;

	//Temp
	thor::Timer mSpawnTimer;

	//Player Temp shit
	//Enemy mEnemy;
	Player* mPlayer;
	
	//Enemy Temp Shit
	std::vector<Enemy*> mEnemy;

	std::vector<Level*> mLevel;
};

