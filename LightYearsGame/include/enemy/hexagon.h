#pragma once
#include "enemy/EnemySpaceShip.h"
#include "weapon/bulletshooter.h"

namespace ly
{
	class BulletShooter;
	class Hexagon : public EnemySpaceShip
	{
	public:
		Hexagon(World* world, const std::string& texturePath = "SpaceShooterRedux/PNG/Enemies/enemyGreen4.png", const sf::Vector2f& velocity = { 0.f, 80.f });
		virtual void Tick(float deltaTime) override;

		virtual void BeginPlay() override;
	private:
		virtual void shoot() override;

		unique<BulletShooter> mShooter1;
		unique<BulletShooter> mShooter2;
		unique<BulletShooter> mShooter3;
		unique<BulletShooter> mShooter4;
		unique<BulletShooter> mShooter5;
		unique<BulletShooter> mShooter6;
	};
}