#pragma once
#include <Level/Level.hpp>

class MainMenuState
	
{
public:
	MainMenuState(sf::RenderWindow* window);
	~MainMenuState();

	void update(const float& deltaTime);
	void render(sf::RenderTarget& target);
	void handleButtonEvents(sf::Event& e);

private:
	void initTextures();
	void gui();
	void setText();

	//SFML Stuff
	sf::RenderWindow* mWindow;
	sf::Font mFont1;
	sf::Font mFont;
	sf::Text mText;
	sf::Texture mBackgroundTexture;
	sf::Sprite mBackgroundSprite;

	tgui::Gui* mGui;

	//Temp Shit
	std::vector<Level*> mLevel;
};

