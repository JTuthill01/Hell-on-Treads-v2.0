#pragma once

namespace Trees
{
	class Tree
	{
	public:
		Tree();
		Tree(std::vector<sf::Texture>& textures, sf::Vector2f position);
		~Tree();

		void render(sf::RenderTarget& target);
		void damaged(int damage);

		inline sf::Vector2f getPosition() { return mTreeSprite.getPosition(); }
		inline sf::Sprite getTreeSprite() { return mTreeSprite; }
		inline int getTreeHp() { return mHp; }

		static std::vector<sf::Texture> treeTextures;

	private:

		bool mIsAlive;

		int mHp;

		std::vector<sf::Texture>* mTextures;

		sf::Vector2f mPosition;
		sf::Texture mTreeTexture;
		sf::Sprite mTreeSprite;
	};

}