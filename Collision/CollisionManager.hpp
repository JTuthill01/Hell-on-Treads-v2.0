#pragma once
#include <Entity/Enemy/Enemy.hpp>
#include <Entity/Entity.hpp>
#include <Entity/Player/Player.hpp>
#include <Collision/Collision.hpp>

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	void playerEnemyTankProjectileCollision();
	void playerPlaneEnemyProjectileCollision();

	void enemyPlayerTankProjectileCollision();
	void enemyPlayerPlaneProjectileCollision();

private:

	//Player
	Player* mPlayer;
	bool mRemovePlayerProjectile;

	//Enemy 
	std::vector<Enemy*> mEnemy;
};

