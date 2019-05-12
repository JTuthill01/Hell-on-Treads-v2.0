#include "pch.hpp"
#include "MainMenuState.hpp"

MainMenuState::MainMenuState(sf::RenderWindow* window) : mWindow(window)
{
	mGui = new tgui::Gui();

	mGui->setTarget(*window);

	initTextures();

	setText();

	gui();
}

MainMenuState::~MainMenuState()
{
	delete mGui;

	mLevel.clear();

	mLevel.shrink_to_fit();
}

void MainMenuState::update(const float& deltaTime)
{
	for (size_t i = 0; i < mLevel.size(); i++)
		mLevel[i]->update(deltaTime);
}

void MainMenuState::render(sf::RenderTarget& target)
{
	target.draw(mBackgroundSprite);

	target.draw(mText);

	mGui->draw();

	for (size_t i = 0; i < mLevel.size(); i++)
		mLevel[i]->render(target);
}

void MainMenuState::handleButtonEvents(sf::Event& e)
{
	mGui->handleEvent(e);
}

void MainMenuState::initTextures()
{
	if (!mBackgroundTexture.loadFromFile("Resources/Textures/Backgrounds/war2.png"))
		std::cerr << "Background failed to load" << "\n";

	mBackgroundSprite.setTexture(mBackgroundTexture);
}

void MainMenuState::gui()
{
	tgui::Theme theme{ "Resources/themes/black.txt" };

	auto mButtons = tgui::Button::create();
	mButtons->setPosition(400, 600);
	mButtons->setRenderer(theme.getRenderer("Button"));
	mButtons->setText("Play");
	mButtons->setTextSize(25U);
	mButtons->setSize(150, 50);
	mButtons->connect("pressed", [&]() { mLevel.emplace_back(new Level(mWindow, mLevel)); });
	mGui->add(mButtons);

	auto mButton = tgui::Button::create();
	mButton->setPosition(400, 700);
	mButton->setRenderer(theme.getRenderer("Button"));
	mButton->setText("Pussy Out");
	mButton->setTextSize(25U);
	mButton->setSize(150, 50);
	mButton->connect("pressed", [&]() { mWindow->close(); });
	mGui->add(mButton);
	
}

void MainMenuState::setText()
{
	if (!mFont1.loadFromFile("Resources/Fonts/Anton-Regular.ttf"))
		std::cerr << "Font failed to load" << "\n";

	if (!mFont.loadFromFile("Resources/Fonts/MetalMacabre.ttf"))
		std::cerr << "Font failed to load" << "\n";

	mText.setFillColor(sf::Color(255, 255, 255, 190));
	mText.setCharacterSize(100U);
	mText.setFont(mFont);
	mText.setString("Hell on Treads");
	mText.setPosition(sf::Vector2f(static_cast<float>(mWindow->getSize().x) / 2 - 450, static_cast<float>(mWindow->getSize().y) - 800.F));
}

