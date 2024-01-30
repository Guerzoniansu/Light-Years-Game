#include "enemy/TwinBlade.h"

namespace ly
{
	TwinBlade::TwinBlade(World* world, const std::string& texturePath, const sf::Vector2f& velocity)
		: EnemySpaceShip{ world, texturePath },
		mShooterLeft{ new BulletShooter{this, 1.0f, {50.f, 20.f} } },
		mShooterRight{ new BulletShooter{this, 1.0f, {50.f, -20.f} } }
	{
		setVelocity(velocity);
		setActorRotation(180.f);
	}
	void TwinBlade::Tick(float deltaTime)
	{
		EnemySpaceShip::Tick(deltaTime);
		shoot();
	}
	void TwinBlade::shoot()
	{
		mShooterLeft->shoot();
		mShooterRight->shoot();
	}
	void TwinBlade::BeginPlay()
	{
		EnemySpaceShip::BeginPlay();
		Health& healthComp = getHealthComp();
		healthComp.setInitialHealth(150.f, 150.f);
	}
}