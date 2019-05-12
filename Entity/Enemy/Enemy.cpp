#include "pch.hpp"
#include "Enemy.hpp"

std::vector<sf::Texture> Enemy::EnemyPlaneWeapons;
std::vector<sf::Texture> Enemy::EnemyJeepWeapons;
std::vector<sf::Texture> Enemy::EnemyTankWeapons;

Enemy::Enemy() = default;

Enemy::Enemy(std::vector<sf::Texture>& projectileTexture, sf::Vector2f position, int enemyType) : mIsAttacking(false), mIsAlive(true), mIsMuzzleOn(false)
{
	mHp = 6;

	mHpMax = 8;

	mDamage = 1;

	mDamageMax = 4;

	pShootTimer.restart(sf::seconds(0.2F));

	mIsAlive = true;

	mEnemyType = enemyType;

	mProjectileTextures = &projectileTexture;

	mPosition = position;

	loadEnemies();

	loadProjectiles();

	loadPlaneProjectiles();

	switch (mEnemyType)
	{

	case TANK_REGULAR:

		createMovementComponent(mEnemySprite, 350.F, 16.F, 6.F);

		createAnimationComponent(mEnemySprite, mEnemyTankTexture);

		pAnimationComponent->addAnimation("MOVE", 5.f, 0, 0, 7, 0, 435, 435);

		pAnimationComponent->addAnimation("ATTACK", 5.f, 0, 1, 7, 1, 435, 435);

		pAnimationComponent->addAnimation("DEAD", 5.f, 0, 2, 10, 2, 435, 435);

		mEnemySprite.setTexture(mEnemyTankTexture);

		mEnemySprite.setPosition(position);

		mEnemySprite.setScale(1.F, 1.F);

		mEnemySprite.setColor(sf::Color(222, 184, 135, 255));

		break;

	case TANK_FIRE:

		mType = FIRE;

		createMovementComponent(mEnemySprite, 350.F, 16.F, 6.F);

		createAnimationComponent(mEnemySprite, mEnemyTankTexture);

		pAnimationComponent->addAnimation("MOVE", 5.f, 0, 0, 7, 0, 435, 435);

		pAnimationComponent->addAnimation("ATTACK", 5.f, 0, 1, 7, 1, 435, 435);

		pAnimationComponent->addAnimation("DEAD", 5.f, 0, 2, 10, 2, 435, 435);

		mEnemySprite.setTexture(mEnemyTankTexture);

		mEnemySprite.setPosition(position);

		mEnemySprite.setScale(1.F, 1.F);

		mEnemySprite.setColor(sf::Color(222, 184, 135, 255));

		break;

	case TANK_ICE:

		mType = ICE;

		createMovementComponent(mEnemySprite, 350.F, 16.F, 6.F);

		createAnimationComponent(mEnemySprite, mEnemyTankTexture);

		pAnimationComponent->addAnimation("MOVE", 5.f, 0, 0, 7, 0, 435, 435);

		pAnimationComponent->addAnimation("ATTACK", 5.f, 0, 1, 7, 1, 435, 435);

		pAnimationComponent->addAnimation("DEAD", 5.f, 0, 2, 10, 2, 435, 435);

		mEnemySprite.setTexture(mEnemyTankTexture);

		mEnemySprite.setPosition(position);

		mEnemySprite.setScale(1.F, 1.F);

		mEnemySprite.setColor(sf::Color(222, 184, 135, 255));

		mIsFrozen = false;

		break;

	case TANK_CORROSIVE:
		
		mType = CORROSIVE;

		createMovementComponent(mEnemySprite, 350.F, 16.F, 6.F);

		createAnimationComponent(mEnemySprite, mEnemyTankTexture);

		pAnimationComponent->addAnimation("MOVE", 5.f, 0, 0, 7, 0, 435, 435);

		pAnimationComponent->addAnimation("ATTACK", 5.f, 0, 1, 7, 1, 435, 435);

		pAnimationComponent->addAnimation("DEAD", 5.f, 0, 2, 10, 2, 435, 435);

		mEnemySprite.setTexture(mEnemyTankTexture);

		mEnemySprite.setPosition(position);

		mEnemySprite.setScale(1.F, 1.F);

		mEnemySprite.setColor(sf::Color(222, 184, 135, 255));

		break;

	case JEEP_REGULAR:

		mType = REGULAR;

		mEnemySprite.setTexture(mEnemyJeepTexture);

		mEnemySprite.setPosition(position);

		mEnemySprite.setScale(1.F, 1.F);

		break;

	case PLANE_REGULAR:

		mType = PLANE_MISSILE;

		mEnemySprite.setTexture(mEnemyPlaneTexture);

		mEnemySprite.setPosition(position);

		mEnemySprite.setScale(-1.F, 1.F);

		break;

	default:
		break;
	}
}

Enemy::~Enemy() = default;

void Enemy::move(const float direction_x, const float direction_y, const float& deltaTime)
{
	if (pMovementComponent)
		pMovementComponent->move(direction_x, direction_y, deltaTime);
}

void Enemy::takeDamage(int damage)
{
	mHp -= damage;

	if (mHp < 0)
	{
		mHp = 0;

		mIsAlive = false;
	}
}

const int Enemy::enemyDealDamage() const
{
	int damage = 0;

	switch (mEnemyType)
	{
	case TANK_REGULAR:

		damage = rand() % mDamage + mDamageMax;

		break;

	case TANK_FIRE:

		damage = rand() % mDamage + 2;

		break;

	case TANK_ICE:

		int frozen;

		damage = rand() % mDamage + mDamageMax + 1;

		frozen = thor::random(0, 4);

		if (frozen == 3)
			mIsFrozen == true;

		break;

	case TANK_CORROSIVE:

		damage = rand() % mDamage + mDamageMax + thor::random(0, 4);

		break;

	case JEEP_REGULAR:

		damage = rand() % mDamage + mDamageMax;

		break;

	case PLANE_REGULAR:

		damage = mDamage + thor::random(0, 3);

		break;

	default:
		break;
	}

	return damage;
}

void Enemy::removeTankProjectile(unsigned index) { mEnemyTankProjectiles.erase(mEnemyTankProjectiles.begin() + index); }

void Enemy::removePlaneProjectile(unsigned index) { mEnemyPlaneProjectiles.erase(mEnemyPlaneProjectiles.begin() + index); }

void Enemy::removeJeepProjectile(unsigned index) { mJeepProjectiles.erase(mJeepProjectiles.begin() + index); }

void Enemy::updateJeep(const float& deltaTime)
{
	mEnemySprite.move(-0.48F, 0.F);

	if (mShootTimer.isExpired() && mIsAlive)
	{
		enemyJeepAttack();

		mShootTimer.restart(sf::seconds(1.5F));
	}

	for (size_t i = 0; i < mJeepProjectiles.size(); i++)
		mJeepProjectiles[i].update(deltaTime);
}

void Enemy::updatePlane(const float& deltaTime)
{
	mEnemyPlaneSprite.move(-0.6F, 0.F);

	if (mPlaneShootTimer.isExpired() && mIsAlive)
	{
		planeShoot();

		mPlaneShootTimer.restart(sf::seconds(1.5F));
	}

	for (size_t i = 0; i < mEnemyPlaneProjectiles.size(); i++)
		mEnemyPlaneProjectiles[i].update(deltaTime);
}

void Enemy::updateTank(const float& deltaTime)
{
	animations(mEnemySprite, deltaTime, pIsAttacking);

	if (pShootTimer.isExpired() && mIsAlive)
	{
		pIsMuzzleOn = true;

		pIsAttacking = true;

		enemyShoot();

		mMuzzle.createMuzzleFlash(sf::Vector2f(mEnemySprite.getPosition().x - 350, mEnemySprite.getPosition().y), sf::Vector2f(0.6F, 0.6F));

		pShootTimer.restart(sf::seconds(2.8F));
	}

	for (size_t i = 0; i < mEnemyTankProjectiles.size(); i++)
		mEnemyTankProjectiles[i].update(deltaTime);
}

void Enemy::updateAttack(const float& deltaTime)
{
	
}

void Enemy::planeShoot()
{
	if (mEnemyPlaneProjectiles.empty())
		loadPlaneProjectiles();

	if (mType == PLANE_MISSILE)
		mEnemyPlaneProjectiles.push_back(Projectile(&Enemy::EnemyPlaneWeapons[PLANE_MISSILE], mEnemyPlaneSprite.getPosition().x,
			mEnemyPlaneSprite.getPosition().y, sf::Vector2f(-0.1F, 0.1F), sf::Vector2f(-1.F, 0.F)));
}

void Enemy::enemyShoot()
{
	if (mEnemyTankProjectiles.empty())
		loadProjectiles();

	switch (mType)
	{
	case REGULAR:
	
		mEnemyTankProjectiles.push_back(Projectile(&Enemy::EnemyTankWeapons[REGULAR], mEnemySprite.getPosition().x + 150, mEnemySprite.getPosition().y + 180,
			sf::Vector2f(0.4F, 0.5F), sf::Vector2f(1.F, 0.F)));

		break;
	
	case FIRE:
	
		mEnemyTankProjectiles.push_back(Projectile(&Enemy::EnemyTankWeapons[FIRE], mEnemySprite.getPosition().x + 150, mEnemySprite.getPosition().y + 180,
			sf::Vector2f(0.4F, 0.5F), sf::Vector2f(1.F, 0.F)));

		for (size_t i = 0; i < mEnemyTankProjectiles.size(); i++)
			mEnemyTankProjectiles[i].setEnemyProjectileColor(sf::Color(139, 0, 0, 255));

		break;
	
	case ICE:
	
		mEnemyTankProjectiles.push_back(Projectile(&Enemy::EnemyTankWeapons[ICE], mEnemySprite.getPosition().x + 150, mEnemySprite.getPosition().y + 180,
			sf::Vector2f(0.4F, 0.5F), sf::Vector2f(1.F, 0.F)));

		for (size_t i = 0; i < mEnemyTankProjectiles.size(); i++)
			mEnemyTankProjectiles[i].setEnemyProjectileColor(sf::Color::Blue);

		break;
	
	case CORROSIVE:
	
		mEnemyTankProjectiles.push_back(Projectile(&Enemy::EnemyTankWeapons[CORROSIVE], mEnemySprite.getPosition().x + 150, mEnemySprite.getPosition().y + 180,
			sf::Vector2f(0.4F, 0.5F), sf::Vector2f(1.F, 0.F)));

		for (size_t i = 0; i < mEnemyTankProjectiles.size(); i++)
			mEnemyTankProjectiles[i].setEnemyProjectileColor(sf::Color(124, 252, 0, 255));

		break;

	default:
		break;
	}
}

void Enemy::render(sf::RenderTarget& target)
{
	target.draw(mEnemySprite);

	target.draw(mEnemyPlaneSprite);

	for (size_t i = 0; i < mEnemyTankProjectiles.size(); i++)
		mEnemyTankProjectiles[i].render(target);

	for (size_t i = 0; i < mEnemyPlaneProjectiles.size(); i++)
		mEnemyPlaneProjectiles[i].render(target);

	for (size_t i = 0; i < mJeepProjectiles.size(); i++)
		mJeepProjectiles[i].render(target);

	if (pIsMuzzleOn)
		mMuzzle.render(target);
}

Projectile& Enemy::getEnemyTankProjectile(unsigned index) { return mEnemyTankProjectiles[index]; }

Projectile& Enemy::getEnemyPlaneProjectile(unsigned index) { return mEnemyPlaneProjectiles[index]; }

Projectile& Enemy::getEnemyJeepProjectile(unsigned index) { return mJeepProjectiles[index]; }

void Enemy::loadEnemies()
{
	if (!mEnemyTankTexture.loadFromFile("Resources/Textures/Enemy/TankCombined.png"))
		std::cerr << "Tank Texture not found" << "\n";

	if (!mEnemyJeepTexture.loadFromFile("Resources/Textures/Enemy/Jeep/Jeep.png"))
		std::cerr << "Jeep Texture not found" << "\n";

	if (!mEnemyPlaneTexture.loadFromFile("Resources/Textures/Enemy/Fokker.png"))
		std::cerr << "Plane Texture not found" << "\n";
}

void Enemy::loadProjectiles()
{
	sf::Texture temp;
	if (!temp.loadFromFile("Resources/Textures/Bullets/Bullet_3.png"))
		std::cerr << "Bullet failed to load" << "\n";

	Enemy::EnemyTankWeapons.push_back(temp);
	Enemy::EnemyTankWeapons.push_back(temp);
	Enemy::EnemyTankWeapons.push_back(temp);
	Enemy::EnemyTankWeapons.push_back(temp);

	Enemy::EnemyJeepWeapons.push_back(temp);
}

void Enemy::loadPlaneProjectiles()
{
	sf::Texture tempPlane;
	if (!tempPlane.loadFromFile("Resources/Textures/Bullets/missile(2).png"))
		std::cerr << "Missile failed to load" << "\n";

	Enemy::EnemyPlaneWeapons.push_back(tempPlane);
}

void Enemy::enemyJeepAttack()
{
	if (EnemyJeepWeapons.empty())
		loadProjectiles();

	mJeepProjectiles.push_back(Projectile(&Enemy::EnemyJeepWeapons[0], mEnemySprite.getPosition().x + 150, mEnemySprite.getPosition().y + 140,
		sf::Vector2f(0.4F, 0.5F), sf::Vector2f(1.F, 0.F)));
}

