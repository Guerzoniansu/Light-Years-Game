#include "enemy/boss.h"
#include "gameplay/health.h"

namespace ly
{
	Boss::Boss(World* world, const std::string& texturePath)
		:EnemySpaceShip{world, texturePath},
		mSpeed{100.f},
		mBaseSpeed{100.f},
		mSwitchDistanceToEdge{100.f},
		mBaseShooterLeft{ this, 1.f, {40.f, -40.f} },
		mBaseShooterRight{this, 1.f, {40.f, 40.f} },
		mThreeWayShooter{ this, 4.f, {100.f, 0.f} },
		mFrontalWiperLeft{ this, 5.f, {80.f, -100.f} },
		mFrontalWiperRight{this, 5.f, {80.f, 100.f} },
		mStage{1},
		mFinalStageShooterLeft{ this, 0.3f, {50.f, -150.f} },
		mFinalStageShooterRight{this, 0.3f, {50.f, 150.f} }
	{
		setActorRotation(180.f);
		setVelocity({ mSpeed, 0.f });
		setRewardSpawnWeight(0.f);

		
	}
	void Boss::Tick(float deltaTime)
	{
		EnemySpaceShip::Tick(deltaTime);
		shootBaseShooters();
		shootThreeWayShooters();
		shootFrontalWiper();
		if (mStage == 4)
		{
			mFinalStageShooterLeft.shoot();
			mFinalStageShooterRight.shoot();
		}
		checkMove();
	}
	void Boss::BeginPlay()
	{
		EnemySpaceShip::BeginPlay();
		Health& healthComp = getHealthComp();
		healthComp.setInitialHealth(30000.f, 30000.f);
		healthComp.onHealthChanged.bindAction(getWeakRef(), &Boss::heathChanged);
	}
	void Boss::checkMove()
	{
		if (getActorLocation().x > getWindowSize().x - mSwitchDistanceToEdge)
		{
			setVelocity({ -mSpeed, 0.f });
		}
		else if (getActorLocation().x < mSwitchDistanceToEdge)
		{
			setVelocity({ mSpeed, 0.f });
		}
	}
	void Boss::shootBaseShooters()
	{
		mBaseShooterLeft.shoot();
		mBaseShooterRight.shoot();
	}
	void Boss::shootThreeWayShooters()
	{
		mThreeWayShooter.shoot();
	}
	void Boss::shootFrontalWiper()
	{
		mFrontalWiperLeft.shoot();
		mFrontalWiperRight.shoot();
	}
	void Boss::heathChanged(float amt, float currentHealth, float maxHealth)
	{
		float percent = currentHealth / maxHealth;
		if (percent < 0.7f && percent > 0.5f)
		{
			setStage(2);
		}
		if (percent < 0.5f && percent > 0.3f)
		{
			setStage(3);
		}
		if (percent < 0.3f)
		{
			setStage(4);
		}
	}
	void Boss::setStage(int newStage)
	{
		mStage = newStage;
		mBaseShooterLeft.setCurrentLevel(mStage);
		mBaseShooterRight.setCurrentLevel(mStage);
		mFrontalWiperLeft.setCurrentLevel(mStage);
		mFrontalWiperRight.setCurrentLevel(mStage);
		mThreeWayShooter.setCurrentLevel(mStage);
		mSpeed = mStage * mBaseSpeed;
	}
}