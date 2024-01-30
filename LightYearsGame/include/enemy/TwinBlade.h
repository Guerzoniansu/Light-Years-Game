#pragma once
#include "enemy/EnemySpaceShip.h"
#include "weapon/bulletshooter.h"

namespace ly
{
	class BulletShooter;
	class TwinBlade: public EnemySpaceShip
	{
	public:
		TwinBlade(World* world, const std::string& texturePath = "SpaceShooterRedux/PNG/Enemies/enemyBlack1.png", const sf::Vector2f& velocity = { 0.f, 100.f });
		virtual void Tick(float deltaTime) override;
		virtual void shoot() override;

		virtual void BeginPlay() override;
	private:
		unique<BulletShooter> mShooterLeft;
		unique<BulletShooter> mShooterRight;
	};
}