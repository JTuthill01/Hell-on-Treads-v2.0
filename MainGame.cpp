#include "pch.hpp"
#include "MainGame.hpp"

MainGame::MainGame() : WIDTH(1920), HEIGHT(1080), mWindow(nullptr), mDeltaTime(0.F)
{
	initWindow();

	initStates();
}

MainGame::~MainGame()
{
	delete mWindow;

	delete mMainMenu;
}

void MainGame::run()
{
	while (mWindow->isOpen())
	{
		deltaTimeClock();

		update(mDeltaTime);

		render(*mWindow);
	}
}

void MainGame::initWindow()
{
	mWindow = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "Hell on Treads v2.0");
}

void MainGame::initStates()
{
	mMainMenu = new MainMenuState(mWindow);
}

void MainGame::update(const float& deltaTime)
{
	gameEvents();

	mMainMenu->update(deltaTime);
}

void MainGame::render(sf::RenderTarget& target)
{
	mWindow->clear();

	mMainMenu->render(*mWindow);

	mWindow->display();
}

void MainGame::gameEvents()
{
	while (mWindow->pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
			mWindow->close();

		mMainMenu->handleButtonEvents(e);
	}
}

void MainGame::deltaTimeClock()
{
	mDeltaTime = mDeltaClock.restart().asSeconds();
}
