#include "pch.hpp"
#include "Player.hpp"

std::vector<sf::Texture> Player::mPlayerTankProjectiles;
std::vector<sf::Texture> Player::mPlayerPlaneProjectiles;

Player::Player() = default;

Player::Player(int playerType) 
{
	loadPlayer();

	loadProjectiles();

	loadPlaneProjectiles();

	mPlayerType = playerType;

	mShootTimer.restart(sf::seconds(0.1F));

	mKeyTimer.restart(sf::seconds(0.1F));

	mIsAlive = true;

	switch (mPlayerType)
	{
	case REGULAR_TANK:

		createMovementComponent(mPlayerSprite, 350.F, 16.F, 6.F);

		createAnimationComponent(mPlayerSprite, mPlayerTexture);

		pAnimationComponent->addAnimation("MOVE", 5.f, 0, 0, 7, 0, 435, 435);

		pAnimationComponent->addAnimation("ATTACK", 5.f, 0, 1, 7, 1, 435, 435);

		pAnimationComponent->addAnimation("DEAD", 5.f, 0, 2, 10, 2, 435, 435);

		mCurrentWeapon = PROJECTILE_REGULAR;

		mPlayerSprite.setTexture(mPlayerTexture);

		mPlayerSprite.setPosition(0.F, 600.F);

		mPlayerSprite.setScale(1.F, 1.F);

		break;

	case FIRE_TANK:

		mCurrentWeapon = PROJECTILE_FIRE;

		mPlayerSprite.setTexture(mPlayerTexture);

		mPlayerSprite.setPosition(0.F, 600.F);

		mPlayerSprite.setScale(1.F, 1.F);

		break;

	case ICE_TANK:

		mCurrentWeapon = PROJECTILE_ICE;

		mPlayerSprite.setTexture(mPlayerTexture);

		mPlayerSprite.setPosition(0.F, 600.F);

		mPlayerSprite.setScale(1.F, 1.F);

		break;

	case CORROSIVE_TANK:

		mCurrentWeapon = PROJECTILE_CORROSIVE;

		mPlayerSprite.setTexture(mPlayerTexture);

		mPlayerSprite.setPosition(0.F, 600.F);

		mPlayerSprite.setScale(1.F, 1.F);

		break;

	case PLANE:

		mPlayerPlaneCurrentWeapon = PROJECTILE_MISSILE;

		mPlayerSprite.setTexture(mPlayerPlaneTexture);

		mPlayerSprite.setPosition(0.F, 600.F);

		mPlayerSprite.setScale(1.F, 1.F);

		break;

	default:
		break;
	}
}

Player::~Player() = default;

void Player::takeDamage(int damage)
{
	damage -= mHp;

	if (mHp < 0)
	{
		mHp = 0;

		mIsAlive = false;
	}
}

const int Player::playerDealDamage() const
{
	/*int damage;

	return damage;*/

	return 0;
}

void Player::removePlaneProjectile(unsigned index) { mPlayerPlaneProjectile.erase(mPlayerPlaneProjectile.begin() + index); }

void Player::removeProjectile(unsigned index) { mPlayerProjectile.erase(mPlayerProjectile.begin() + index); }

void Player::updateSoldier(const float& deltaTime)
{
}

void Player::updatePlane(const float& deltaTime)
{
	planeAttack();

	for (size_t i = 0; i < mPlayerPlaneProjectile.size(); i++)
		mPlayerPlaneProjectile[i].update(deltaTime);

	playerPlaneInput(deltaTime);
}

void Player::updateTank(const float& deltaTime)
{
	attack();

	animations(mPlayerSprite, deltaTime, pIsAttacking);

	for (size_t i = 0; i < mPlayerProjectile.size(); i++)
		mPlayerProjectile[i].update(deltaTime);

	playerInput(deltaTime);
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(mPlayerSprite);

	target.draw(mAnimationText);

	for (size_t i = 0; i < mPlayerProjectile.size(); i++)
		mPlayerProjectile[i].render(target);

	for (size_t i = 0; i < mPlayerPlaneProjectile.size(); i++)
		mPlayerPlaneProjectile[i].render(target);
}

Projectile& Player::getPlayerProjectile(unsigned index) { return mPlayerProjectile[index]; }

Projectile& Player::getPlayerPlaneProjectile(unsigned index) { return mPlayerPlaneProjectile[index]; }

void Player::loadPlayer()
{
	if (!mPlayerTexture.loadFromFile("Resources/Textures/Player/Combined.png"))
		std::cerr << "Player tank failed to load" << "\n";

	if (!mPlayerPlaneTexture.loadFromFile("Resources/Textures/Player/Plane/Fokker.png"))
		std::cerr << "Player plane failed to load" << "\n";
}

void Player::playerInput(const float& deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		mPlayerSprite.move(0.45F, 0.F);

		move(0.45F, 0.F, deltaTime);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		move(-0.45F, 0.F, deltaTime);
}

void Player::playerPlaneInput(const float& deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		mPlayerSprite.move(0.5F, 0.F);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		mPlayerSprite.move(-0.5F, 0.F);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		mPlayerSprite.move(0.F, -0.5F);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		mPlayerSprite.move(0.F, 0.5F);
}

void Player::currentPlaneWeapon()
{
	if (mPlayerPlaneProjectile.empty())
		loadPlaneProjectiles();

	if (mPlayerPlaneCurrentWeapon == PROJECTILE_MISSILE)
		mPlayerPlaneProjectile.push_back(Projectile(&Player::mPlayerPlaneProjectiles[PROJECTILE_MISSILE], sf::Vector2f(mPlayerPlaneSprite.getPosition().x + 300,
			mPlayerPlaneSprite.getPosition().y + 150), sf::Vector2f(-0.1F, 0.1F), sf::Vector2f(1.F, 0.F)));
}

void Player::currentWeapon()
{
	if (mPlayerProjectile.empty())
		loadProjectiles();

	switch (mCurrentWeapon)
	{
	case PROJECTILE_REGULAR:

		mPlayerProjectile.push_back(Projectile(&Player::mPlayerTankProjectiles[PROJECTILE_REGULAR], sf::Vector2f(mPlayerSprite.getPosition().x + 300, mPlayerSprite.getPosition().y + 195),
			sf::Vector2f(-0.4F, 0.5F), sf::Vector2f(1.F, 0.F)));
		break;

	case PROJECTILE_FIRE:

		mPlayerProjectile.push_back(Projectile(&Player::mPlayerTankProjectiles[PROJECTILE_FIRE], sf::Vector2f(mPlayerSprite.getPosition().x + 300, mPlayerSprite.getPosition().y + 195),
			sf::Vector2f(-0.4F, 0.5F), sf::Vector2f(1.F, 0.F)));

		for (size_t i = 0; i < mPlayerProjectile.size(); i++)
			mPlayerProjectile[i].setProjectileColor(sf::Color(139, 0, 0, 255));

		break;

	case PROJECTILE_ICE:

		mPlayerProjectile.push_back(Projectile(&Player::mPlayerTankProjectiles[PROJECTILE_ICE], sf::Vector2f(mPlayerSprite.getPosition().x + 300, mPlayerSprite.getPosition().y + 195),
			sf::Vector2f(-0.4F, 0.5F), sf::Vector2f(1.F, 0.F)));

		for (size_t i = 0; i < mPlayerProjectile.size(); i++)
			mPlayerProjectile[i].setProjectileColor(sf::Color::Blue);

		break;

	case PROJECTILE_CORROSIVE:

		mPlayerProjectile.push_back(Projectile(&Player::mPlayerTankProjectiles[PROJECTILE_CORROSIVE], sf::Vector2f(mPlayerSprite.getPosition().x + 300, mPlayerSprite.getPosition().y + 195),
			sf::Vector2f(-0.4F, 0.5F), sf::Vector2f(1.F, 0.F)));

		for (size_t i = 0; i < mPlayerProjectile.size(); i++)
			mPlayerProjectile[i].setProjectileColor(sf::Color(124, 252, 0, 255));

		break;

	default:
		break;
	}
}

void Player::planeAttack()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mShootTimer.isExpired() && mKeyTimer.isExpired() && mIsAlive)
	{
		currentPlaneWeapon();

		mShootTimer.restart(sf::seconds(0.5F));

		mKeyTimer.restart(sf::seconds(0.5F));
	}
}

void Player::attack()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mShootTimer.isExpired() && mKeyTimer.isExpired() && mIsAlive)
	{
		currentWeapon();

		mIsMuzzleOn = true;

		mMuzzle.createMuzzleFlash(sf::Vector2f(this->mPlayerSprite.getPosition().x + 150, this->mPlayerSprite.getPosition().y - 10), sf::Vector2f(0.6F, 0.5F));

		mShootTimer.restart(sf::seconds(0.5F));

		mKeyTimer.restart(sf::seconds(0.5F));
	}
}

void Player::initVariables()
{
	mIsMuzzleOn = false;

	mIsAlive = true;

	mKeyTimer.restart(sf::seconds(0.2F));

	mShootTimer.restart(sf::seconds(0.1F));
}

void Player::loadProjectiles()
{
	sf::Texture temp;
	if (!temp.loadFromFile("Resources/Textures/Bullets/Bullet_3.png"))
		std::cerr << "The fucking bullet texture failed to fucking load" << "\n";

	Player::mPlayerTankProjectiles.push_back(temp);
	Player::mPlayerTankProjectiles.push_back(temp);
	Player::mPlayerTankProjectiles.push_back(temp);
	Player::mPlayerTankProjectiles.push_back(temp);
}

void Player::loadPlaneProjectiles()
{
	sf::Texture temp;
	if (!temp.loadFromFile("Resources/Textures/Bullets/missile(2).png"))
		std::cerr << "Missile failed to load" << "\n";
	
	Player::mPlayerPlaneProjectiles.push_back(temp);
}

