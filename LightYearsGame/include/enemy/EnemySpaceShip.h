#pragma once
#include "SpaceShip/spaceship.h"
#include "Player/reward.h"

namespace ly
{
	class EnemySpaceShip:public SpaceShip
	{
	public:
		EnemySpaceShip(World* owningWorld,
			const std::string& texturePath,
			float collisionDamage = 200.f,
			float rewardSpawnRate = 0.5f,
			const list<rewardFactoryFunc> rewards = {
				createHealthReward,
				createThreeWayShooterReward,
				createFrontalWiperReward,
				createLifeReward
			}
		);
		virtual void Tick(float deltaTime) override;
		void setScoreAwardAmt(unsigned int amt);
		unsigned int getScoreAwardAmt() { return mScoreAwardAmt; }
		void setRewardSpawnWeight(float weight);
	private:
		virtual void spawnReward();
		float mCollisionDamage;
		unsigned int mScoreAwardAmt;
		float mRewardSpawnWeight;
		virtual void onActorBeginOverlap(Actor* other) override;
		virtual void Blew() override;
		list<rewardFactoryFunc> mRewardFactories;
	};
}