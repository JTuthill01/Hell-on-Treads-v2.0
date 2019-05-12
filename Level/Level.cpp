#include "pch.hpp"
#include "Level.hpp"

Level::Level(sf::RenderWindow* window, std::vector<Level*> level) : mWindow(window), mLevel(level), mPlayer(nullptr)
{
	if (!mTexture.loadFromFile("Resources/Textures/Backgrounds/war.png"))
		std::cerr << "Failed to load" << "\n";

	mSprite.setTexture(mTexture);

	mPlayer = new Player(TANK_REGULAR);

	mSpawnTimer.restart(sf::seconds(0.2F));
}

Level::~Level()
{
	delete mPlayer;
}

void Level::update(const float& deltaTime)
{
	mPlayer->updateTank(deltaTime);

	mPlayer->move(0.45F, 0, deltaTime);

	if (mSpawnTimer.isExpired())
	{
		mEnemy.push_back(new Enemy(Enemy::EnemyTankWeapons, sf::Vector2f(900, 310), TANK_REGULAR));

		mSpawnTimer.restart(sf::seconds(6.F));
	}

	for (size_t i = 0; i < mEnemy.size(); i++)
	{
		mEnemy[i]->updateTank(deltaTime);

		mEnemy[i]->updatePlane(deltaTime);

		mEnemy[i]->updateJeep(deltaTime);

		mEnemy[i]->move(0.6F, 0.F, deltaTime);
	}
}

void Level::render(sf::RenderTarget& target)
{
	target.draw(mSprite);

	mPlayer->render(target);

	for (size_t i = 0; i < mEnemy.size(); i++)
		mEnemy[i]->render(target);
}

