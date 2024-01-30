#include "enemy/hexagon.h"

namespace ly
{
	Hexagon::Hexagon(World* world, const std::string& texturePath, const sf::Vector2f& velocity)
		: EnemySpaceShip{world, texturePath},
		mShooter1{new BulletShooter{this, 1.0f, {30.f, 50.f}, -60.f}},
		mShooter2{new BulletShooter{this, 1.0f, {30.f, -50.f}, 60.f}},
		mShooter3{new BulletShooter{this, 1.0f, {50.f, 0.f}}},
		mShooter4{new BulletShooter{this, 1.0f, {-30.f, -50.f}, 120.f}},
		mShooter5{new BulletShooter{this, 1.0f, {-30.f, 50.f}, -120.f}},
		mShooter6{new BulletShooter{this, 1.0f, {-50.f, 0.f}, 180.f}}
	{
		setVelocity(velocity);
		setActorRotation(180.f);
	}
	void Hexagon::Tick(float deltaTime)
	{
		EnemySpaceShip::Tick(deltaTime);
		shoot();
	}
	void Hexagon::BeginPlay()
	{
		EnemySpaceShip::BeginPlay();
		Health& healthComp = getHealthComp();
		healthComp.setInitialHealth(250.f, 250.f);
	}
	void Hexagon::shoot()
	{
		mShooter1->shoot();
		mShooter2->shoot();
		mShooter3->shoot();
		mShooter4->shoot();
		mShooter5->shoot();
		mShooter6->shoot();
	}
}