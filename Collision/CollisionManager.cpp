#include "pch.hpp"
#include "CollisionManager.hpp"

CollisionManager::CollisionManager()
{
	mRemovePlayerProjectile = false;
}

CollisionManager::~CollisionManager()
{
	delete mPlayer;
}

void CollisionManager::playerEnemyTankProjectileCollision()
{
	for (int i = 0; i < mPlayer->getPlayerTankProjectileSize(); i++)
	{
		for (size_t j = 0; j < mEnemy.size(); j++)
		{
			if (Collision::BoundingBoxTest(mPlayer->getPlayerProjectile(i).getPlayerProjectileSprite(), mEnemy[i]->getEnemySprite()))
			{
				if (mEnemy[j]->getEnemyHp() > 0)
				{
					int damage = mPlayer->playerDealDamage();

					mEnemy[j]->takeDamage(damage);

					mRemovePlayerProjectile = true;
				}
			}
		}
	}
}

void CollisionManager::playerPlaneEnemyProjectileCollision()
{
	for (int i = 0; i < mPlayer->getPlayerPlaneProjectileSize(); i++)
	{
		for (size_t j = 0; j < mEnemy.size(); j++)
		{
			if (Collision::BoundingBoxTest(mPlayer->getPlayerPlaneProjectile(i).getPlayerProjectileSprite(), mEnemy[j]->getEnemyPlaneSprite()))
			{
				int damage = mPlayer->playerDealDamage();

				if (mEnemy[j]->getEnemyHp() > 0)
				{
					mEnemy[j]->takeDamage(damage);

					mRemovePlayerProjectile = true;
				}
			}
		}
	}
}

void CollisionManager::enemyPlayerTankProjectileCollision()
{

}

void CollisionManager::enemyPlayerPlaneProjectileCollision()
{
}
