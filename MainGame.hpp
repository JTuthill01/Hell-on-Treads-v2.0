#pragma once
#include <States/MainMenuState.hpp>
#include <Level/Level.hpp>

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

private:
	void initWindow();
	void initStates();
	void update(const float& deltaTime);
	void render(sf::RenderTarget& target);
	void gameEvents();
	void deltaTimeClock();

	MainMenuState* mMainMenu;

	sf::RenderWindow* mWindow;
	sf::Clock mDeltaClock;
	sf::Event e;

	float mDeltaTime;

	int WIDTH, HEIGHT;
};

