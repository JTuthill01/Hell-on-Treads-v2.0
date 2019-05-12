#include "pch.hpp"
#include "Projectile.hpp"

Projectile::Projectile() = default;

Projectile::Projectile(sf::Texture* texture, sf::Vector2f position, sf::Vector2f scale, sf::Vector2f direction)
{
	mProjectileTexture = texture;
	mProjectileSprite.setTexture(*this->mProjectileTexture);

	mPosition = position;
	mScale = scale;
	mDirection = direction;

	mProjectileSprite.setScale(scale);
	mProjectileSprite.setPosition(position);
	mProjectileSprite.setRotation(atan2(this->mDirection.y, this->mDirection.x) * 180 / thor::Pi + 180);
}

Projectile::Projectile(sf::Texture* Enemytexture, float x, float y, sf::Vector2f scale, sf::Vector2f direction)
{
	mEnemyProjectileTexture = Enemytexture;
	mEnemyProjectileSprite.setTexture(*mEnemyProjectileTexture);

	mPosition.x = x;
	mPosition.y = y;

	mScale = scale;
	mDirection = direction;

	mEnemyProjectileSprite.setScale(scale);
	mEnemyProjectileSprite.setPosition(x, y);
	mEnemyProjectileSprite.setRotation(atan2(this->mDirection.y, this->mDirection.x) * 180 / thor::Pi + 180);
}

Projectile::~Projectile() = default;

void Projectile::render(sf::RenderTarget& target)
{
	target.draw(mProjectileSprite);

	target.draw(mEnemyProjectileSprite);

	target.draw(mMuzzleSprite);
}

void Projectile::update(const float& deltaTime)
{
	movement(deltaTime);
}

void Projectile::movement(const float& deltaTime)
{
	mProjectileSprite.move(8.F * deltaTime * 62.5F, 0.F);

	mEnemyProjectileSprite.move(-8.F * deltaTime * 62.5F, 0.F);
}

void Projectile::createMuzzleFlash(sf::Vector2f position, sf::Vector2f scale)
{
	if (!mMuzzleTexture.loadFromFile("Resources/Textures/Explosions/explosion.png"))
		std::cerr << "Muzzle Texture failed to load" << "\n";

	mMuzzleSprite.setTexture(mMuzzleTexture);
	mMuzzleSprite.setPosition(position);
	mMuzzleSprite.setScale(scale);
}
