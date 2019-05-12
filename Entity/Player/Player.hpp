#pragma once
#include <Entity/Entity.hpp>
#include <Projectile/Projectile.hpp>

enum player { REGULAR_TANK = 0, FIRE_TANK, ICE_TANK, CORROSIVE_TANK, PLANE };

enum playerProjectileType { PROJECTILE_REGULAR = 0, PROJECTILE_FIRE, PROJECTILE_ICE, PROJECTILE_CORROSIVE };

enum playerPlaneProjectile { PROJECTILE_MISSILE = 0 };

class Player :
	public Entity
{
public:
	Player();
	Player(int weaponType);
	~Player();

	//Functions
	void takeDamage(int damage);
	const int playerDealDamage() const;
	void removePlaneProjectile(unsigned index);
	void removeProjectile(unsigned index);
	void updateSoldier(const float& deltaTime);
	void updatePlane(const float& deltaTime);
	void updateTank(const float& deltaTime);
	void render(sf::RenderTarget& target);

	//Inline
	const inline int getPlayerTankProjectileSize() { return mPlayerProjectile.size(); }
	const inline int getPlayerPlaneProjectileSize() { return mPlayerPlaneProjectile.size(); }
	const inline sf::Vector2f& getPlayerPlanePosition() { return mPlayerPlaneSprite.getPosition(); }
	const inline sf::Vector2f& getPlayerPosition() { return mPlayerSprite.getPosition(); }
	const inline sf::Sprite& getPlayerSprite() { return mPlayerSprite; }
	const inline sf::Sprite& getPlayerPlaneSprite() { return mPlayerPlaneSprite; }

	//Static
	static std::vector<sf::Texture> mPlayerTankProjectiles;
	static std::vector<sf::Texture> mPlayerPlaneProjectiles;

	//Projectiles
	Projectile& getPlayerProjectile(unsigned index);
	Projectile& getPlayerPlaneProjectile(unsigned index);

private:
	//Functions
	void loadPlayer();
	void playerInput(const float& deltaTime);
	void playerPlaneInput(const float& deltaTime);
	void currentPlaneWeapon();
	void currentWeapon();
	void planeAttack();
	void attack();
	void initVariables();
	void loadProjectiles();
	void loadPlaneProjectiles();

	//Player 
	sf::Texture mPlayerPlaneTexture;
	sf::Sprite mPlayerPlaneSprite;

	sf::Text mAnimationText;
	sf::Font mFont;

	int mPlayerType;
	int mCurrentWeapon;
	int mPlayerPlaneCurrentWeapon;

	sf::Texture mPlayerTexture;
	sf::Sprite mPlayerSprite;

	sf::Vector2f mPosition;

	//HP
	int mHp;
	int mHpMax;

	//Damage
	int mDamage;
	int mDamageMax;

	//Projectile
	Projectile mMuzzle;
	std::vector<sf::Texture>* mProjectileTextures;
	std::vector<Projectile> mPlayerProjectile;
	std::vector<Projectile> mPlayerPlaneProjectile;

	//Timers
	thor::Timer mShootTimer;
	thor::Timer mKeyTimer;
	sf::Clock mClock;

	//Booleans
	bool mIsMuzzleOn;
	bool mIsAlive;

};

