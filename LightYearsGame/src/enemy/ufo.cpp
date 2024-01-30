#include "enemy/ufo.h"

namespace ly
{
	UFO::UFO(World* world, const sf::Vector2f& velocity, const std::string& texturePath, float rotationSpeed)
		:EnemySpaceShip{world, texturePath},
		mRotationSpeed{rotationSpeed},
		mShooter2{new BulletShooter{this, 0.5f, sf::Vector2f{0.f, 0.f}, -120.f}},
		mShooter1{new BulletShooter{this, 0.5f}},
		mShooter3{new BulletShooter{this, 0.5f, sf::Vector2f{0.f, 0.f}, 120.f}}
	{
		setVelocity(velocity);
		setActorRotation(180.f);
	}

	void UFO::Tick(float deltaTime)
	{
		EnemySpaceShip::Tick(deltaTime);
		shoot();
		addActorRotationOffset(mRotationSpeed * deltaTime);
	}

	void UFO::shoot()
	{
		mShooter1->shoot();
		mShooter2->shoot();
		mShooter3->shoot();
	}
}