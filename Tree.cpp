#include "pch.hpp"
#include "Tree.hpp"

namespace Trees
{
	std::vector<sf::Texture> Trees::Tree::treeTextures;

	Tree::Tree() : mHp(2), mIsAlive(true), mTextures(nullptr)
	{
		if (!mTreeTexture.loadFromFile("Resources/Trees/trees.png"))
			std::cerr << "Texture not found" << "\n";

		mTreeSprite.setTexture(mTreeTexture);
		mTreeSprite.setPosition(sf::Vector2f(700, 210));
		mTreeSprite.setScale(2.F, 2.F);
		mTreeSprite.setColor(sf::Color::Yellow);
	}

	Tree::Tree(std::vector<sf::Texture>& textures, sf::Vector2f position) : mHp(2), mIsAlive(true)
	{
		mTextures = &textures;
		mPosition = position;

		mTreeSprite.setTexture((*mTextures)[0]);
		mTreeSprite.setPosition(position);
		mTreeSprite.setScale(2.F, 2.F);
		mTreeSprite.setColor(sf::Color(165, 42, 42, 255));
	}

	Tree::~Tree() = default;

	void Tree::render(sf::RenderTarget& target) { target.draw(mTreeSprite); }

	void Tree::damaged(int damage)
	{
		mHp -= damage;

		if (mHp <= 0)
		{
			mHp = 0;

			mIsAlive = false;
		}
	}
}