#pragma once
#include "enemy/EnemySpaceShip.h"
#include "weapon/bulletshooter.h"

namespace ly
{
	class BulletShooter;
	class UFO : public EnemySpaceShip
	{
	public:
		UFO(World* world, const sf::Vector2f& velocity, const std::string& texturePath = "SpaceShooterRedux/PNG/ufoBlue.png", float rotationSpeed = 80.f);
		virtual void Tick(float deltaTime) override;

	private:
		virtual void shoot() override;
		float mRotationSpeed;

		unique<BulletShooter> mShooter1;
		unique<BulletShooter> mShooter2;
		unique<BulletShooter> mShooter3;
	};
}