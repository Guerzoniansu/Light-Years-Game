#pragma once
#include "enemy/EnemySpaceShip.h"
#include "framework/world.h"
#include "weapon/bulletshooter.h"
#include "weapon/threeWayShooter.h"
#include "weapon/FrontalWiper.h"

namespace ly
{
	class Boss : public EnemySpaceShip
	{
	public:
		Boss(World* world, const std::string& texturePath = "SpaceShooterRedux/PNG/Enemies/boss.png");
		virtual void Tick(float deltaTime) override;
		virtual void BeginPlay() override;

	private:
		float mSpeed;
		float mBaseSpeed;
		float mSwitchDistanceToEdge;
		void checkMove();

		BulletShooter mBaseShooterLeft;
		BulletShooter mBaseShooterRight;

		ThreeWayShooter mThreeWayShooter;
		FrontalWiper mFrontalWiperLeft;
		FrontalWiper mFrontalWiperRight;

		BulletShooter mFinalStageShooterLeft;
		BulletShooter mFinalStageShooterRight;

		void shootBaseShooters();
		void shootThreeWayShooters();
		void shootFrontalWiper();

		void heathChanged(float amt, float currentHealth, float maxHealth);
		void setStage(int newStage);

		int mStage;
	};
}