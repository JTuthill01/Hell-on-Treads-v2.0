#include "pch.hpp"
#include "Entity.hpp"

Entity::Entity() : pIsFrozen(false), pIsEnemyAlive(true), pIsPlayerAlive(true), pWindow(nullptr), pIsAttacking(false)
{
}

Entity::~Entity()
{
}

void Entity::updateAttacks(bool isAttacking)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) | pShootTimer.isExpired())
		isAttacking = true;
}

void Entity::animations(sf::Sprite& sprite, const float& deltaTime, bool isAttacking)
{
	pIsAttacking = isAttacking;

	if (pIsAttacking)
	{
		if (sprite.getScale().x > 0.f) //Facing left
			sprite.setOrigin(96.f, 0.f);

		if (this->pAnimationComponent->play("ATTACK", deltaTime, true))
		{
			pIsAttacking = false;

			pIsMuzzleOn = false;

			if (sprite.getScale().x > 0.f) //Facing left
				sprite.setOrigin(0.f, 0.f);
		}
	}

	else if (pMovementComponent->getState(MOVING))
	{
		if (sprite.getScale().x < 0.f)
		{
			sprite.setOrigin(0.f, 0.f);
			sprite.setScale(1.f, 1.f);
		}

		this->pAnimationComponent->play("MOVE", deltaTime, pMovementComponent->getVelocity().x, pMovementComponent->getMaxVelocity());
	}

	else if (this->pMovementComponent->getState(MOVING))
	{
		if (sprite.getScale().x < 0.f)
		{
			sprite.setOrigin(140.f, 0.f);
			sprite.setScale(1.f, 1.f);
		}

		pAnimationComponent->play("MOVE", deltaTime, pMovementComponent->getVelocity().x, pMovementComponent->getMaxVelocity());
	}
}

void Entity::createMovementComponent(sf::Sprite& sprite, const float max_velocity, const float acceleration, const float deceleration)
{
	pMovementComponent = new MovementComponent(sprite, max_velocity, acceleration, deceleration);
}

void Entity::createAnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet)
{
	pAnimationComponent = new AnimationComponent(sprite, texture_sheet);
}

void Entity::move(const float direction_x, const float direction_y, const float& deltaTime)
{
	if (pMovementComponent)
		pMovementComponent->move(direction_x, direction_y, deltaTime);
}

