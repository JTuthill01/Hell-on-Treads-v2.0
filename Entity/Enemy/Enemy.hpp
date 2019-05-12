#pragma once
#include <Projectile/Projectile.hpp>
#include "Entity/Entity.hpp"

enum enemyType { TANK_REGULAR = 0, TANK_FIRE, TANK_ICE, TANK_CORROSIVE, JEEP_REGULAR, PLANE_REGULAR };

enum planeProjectile { PLANE_MISSILE };

enum projectileType { REGULAR = 0, FIRE, ICE, CORROSIVE };

class Enemy : Entity
{
public:
	Enemy();
	Enemy(std::vector<sf::Texture>& projectileTexture, sf::Vector2f position, int enemyType);
	~Enemy();

	//Public Functions
	void move(const float direction_x, const float direction_y, const float& deltaTime);
	void takeDamage(int damage);
	const int enemyDealDamage() const;
	void removeTankProjectile(unsigned index);
	void removePlaneProjectile(unsigned index);
	void removeJeepProjectile(unsigned index);
	void updateJeep(const float& deltaTime);
	void updatePlane(const float& deltaTime);
	void updateTank(const float& deltaTime);
	void updateAttack(const float& deltaTime);
	void planeShoot();
	void enemyShoot();
	void render(sf::RenderTarget& target);

	//Inline Getter(s)
	const inline int getEnemyTankProjectileSize() { return mEnemyTankProjectiles.size(); }
	const inline int getEnemyPlaneProjectileSize() { return mEnemyPlaneProjectiles.size(); }
	inline int getEnemyHp() { return mHp; }
	inline sf::Sprite getEnemySprite() { return mEnemySprite; }
	inline sf::Sprite getEnemyPlaneSprite() { return mEnemyPlaneSprite; }
	inline sf::Vector2f getEnemyPosition() { return mEnemySprite.getPosition(); }
	inline sf::Vector2f getEnemyPlanePosition() { return mEnemyPlaneSprite.getPosition(); }
	inline bool getIsFrozen() { return mIsFrozen; }

	//Projectiles
	Projectile& getEnemyTankProjectile(unsigned index);
	Projectile& getEnemyPlaneProjectile(unsigned index);
	Projectile& getEnemyJeepProjectile(unsigned index);

	static std::vector<sf::Texture> EnemyTankWeapons;
	static std::vector<sf::Texture> EnemyJeepWeapons;
	static std::vector<sf::Texture> EnemyPlaneWeapons;

private:
	//Private Functions
	void loadEnemies();
	void loadProjectiles();
	void loadPlaneProjectiles();
	void enemyJeepAttack();

	//Booleans
	bool mIsAlive;
	bool mIsAttacking;
	bool mIsFiring;
	bool mIsMuzzleOn;
	bool mIsFrozen;

	//Enemies + weapon textures
	sf::Texture mEnemyTankTexture;
	sf::Texture mEnemyJeepTexture;
	sf::Texture mEnemyPlaneTexture;

	std::vector<sf::Texture>* mProjectileTextures;

	Projectile mEnemyTankProjectile;
	std::vector<Projectile> mJeepProjectiles;
	std::vector<Projectile> mEnemyTankProjectiles;
	std::vector<Projectile> mEnemyPlaneProjectiles;

	//Muzzle Flash
	Projectile mMuzzle;

	//Enemy Sprites
	sf::Sprite mEnemySprite;
	sf::Sprite mEnemyPlaneSprite;

	//Movement
	sf::Vector2f mPosition;
	sf::Vector2f mDirection;

	//Timers
	thor::Timer mShootTimer;
	thor::Timer mPlaneShootTimer;
	thor::Timer mMuzzleTimer;

	int mType;
	int mEnemyType;
	int enemyPlaneType;
	int mHp;
	int mHpMax;
	int mDamage;
	int mDamageMax;
};

