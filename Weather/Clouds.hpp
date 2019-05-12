#pragma once

class Clouds 
{
public:
	Clouds(std::vector<sf::Texture>& texture, sf::Vector2f position);
	virtual ~Clouds();

	void render(sf::RenderTarget& target);
	void update(const float& deltaTime);

	inline sf::Vector2f getCloudPosition() { return mCloudSprite.getPosition(); }

private:
	//Clouds
	sf::Vector2f mCloudPosition;
	sf::Texture mCloudsTexture;
	sf::Sprite mCloudSprite;
	std::vector<sf::Texture>* mClouds;

};

