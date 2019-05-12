#pragma once
#include <Component/AnimationComponent.h>
#include <Component/MovementComponent.h>

class Entity
{
public:
	Entity();
	virtual ~Entity();

	virtual void updateAttacks(bool isAttacking);
	virtual void animations(sf::Sprite& sprite, const float& deltaTime, bool isAttacking);
	virtual void createMovementComponent(sf::Sprite& sprite, const float max_velocity, const float acceleration, const float deceleration);
	virtual void createAnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet);
	virtual void move(const float direction_x, const float direction_y, const float& deltaTime);
	
	inline const bool getCorrosive() { return pIsCorrosiveShot; }
	inline const bool getFire() { return pIsFireShot; }
	inline const bool getFrozen() { return this->pIsIceShot; }

	void setIsEnemyAlive(bool t_f) { pIsEnemyAlive = t_f; }
	void setIsPlayerAlive(bool t_f) { pIsPlayerAlive = t_f; }

protected:
	//Animations
	MovementComponent* pMovementComponent;
	AnimationComponent* pAnimationComponent;

	//Timer(s)
	thor::Timer pEnemyJeepShootTimer;
	thor::Timer pEnemyPlaneShootTimer;
	thor::Timer pEnemyTankShootTimer;
	thor::Timer pShootTimer;

	sf::RenderWindow* pWindow;

	//Turret
	sf::Texture pTurretTexture;
	sf::Sprite pTurretSprite;

	//Hp Bar
	sf::RectangleShape pHpBar1;
	sf::RectangleShape pHpBar2;
	sf::RectangleShape pHpBar3;
	sf::RectangleShape pHpBar4;

	//Weapons
	int pCurrentWeapon;

	bool pIsMuzzleOn;
	bool pIsFireShot;
	bool pIsIceShot;
	bool pIsFrozen;
	bool pIsCorrosiveShot;
	bool pIsEnemyAlive;
	bool pIsPlayerAlive;
	bool pIsAttacking;

	//Damage
	int pFrozen;

	int mEnemyType;
};

