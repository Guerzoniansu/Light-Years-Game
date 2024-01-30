#include "enemy/vanguard.h"
#include "weapon/bulletshooter.h"

namespace ly
{
	Vanguard::Vanguard(World* owningWorld, const std::string& texturePath, const sf::Vector2f& velocity)
		:EnemySpaceShip{ owningWorld, texturePath },
		mShooter{ new BulletShooter{this, 1.0f, {50.f, 0.f}} }
	{
		setVelocity(velocity);
		setActorRotation(180.f);
	}

	void Vanguard::Tick(float deltaTime)
	{
		EnemySpaceShip::Tick(deltaTime);
		shoot();
	}

	void Vanguard::shoot()
	{
		mShooter->shoot();
	}
}