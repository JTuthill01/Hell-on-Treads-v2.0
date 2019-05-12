#pragma once
class Projectile
{
public:
	Projectile();
	Projectile(sf::Texture* texture, sf::Vector2f position, sf::Vector2f scale, sf::Vector2f direction);
	Projectile(sf::Texture* Enemytexture, float x, float y, sf::Vector2f scale, sf::Vector2f direction);

	~Projectile();

	void render(sf::RenderTarget& target);
	void update(const float& deltaTime);
	void movement(const float& deltaTime);
	void createMuzzleFlash(sf::Vector2f position, sf::Vector2f scale);
	void setProjectileColor(sf::Color color) { mProjectileSprite.setColor(color); }
	void setEnemyProjectileColor(sf::Color color) { mEnemyProjectileSprite.setColor(color); }

	inline const sf::Vector2f& getEnemyProjectile(sf::Sprite spriteProjectile) { return spriteProjectile.getPosition(); }
	inline const sf::Vector2f& getPlayerProjectilePosition() { return mProjectileSprite.getPosition(); }
	inline const sf::Sprite& getEnemyProjectileSprite() { return mEnemyProjectileSprite; }
	inline const sf::Sprite& getPlayerProjectileSprite() { return mProjectileSprite; }

private:
	//Muzzle flash
	sf::Texture mMuzzleTexture;
	sf::Sprite mMuzzleSprite;

	//Player
	sf::Texture* mProjectileTexture;
	sf::Sprite mProjectileSprite;

	//Enemy
	sf::Texture* mEnemyProjectileTexture;
	sf::Sprite mEnemyProjectileSprite;

	sf::Vector2f mPosition;
	sf::Vector2f mScale;
	sf::Vector2f mDirection;
};

