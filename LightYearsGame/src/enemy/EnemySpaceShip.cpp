#include "enemy/EnemySpaceShip.h"
#include "framework/math.h"
#include "Player/PlayerManager.h"

namespace ly
{
	EnemySpaceShip::EnemySpaceShip(World* owningWorld, const std::string& texturePath,
		float collisionDamage, float rewardSpawnRate, const list<rewardFactoryFunc> rewards)
		:SpaceShip{ owningWorld, texturePath },
		mCollisionDamage{ collisionDamage },
		mRewardFactories{rewards},
		mScoreAwardAmt{10},
		mRewardSpawnWeight{rewardSpawnRate}
	{
		setTeamID(2);
	}
	void EnemySpaceShip::Tick(float deltaTime)
	{
		SpaceShip::Tick(deltaTime);
		if (isActorOutOfWindowBounds(getActorGlobalBounds().width * 2.f))
		{
			Destroy();
		}
	}
	void EnemySpaceShip::setScoreAwardAmt(unsigned int amt)
	{
		mScoreAwardAmt = amt;
	}
	void EnemySpaceShip::Blew()
	{
		spawnReward();
		Player* player = PlayerManager::get().getPlayer();
		if (player)
		{
			player->addScore(mScoreAwardAmt);
		}
	}
	void EnemySpaceShip::spawnReward()
	{
		if (mRewardFactories.size() == 0)
		{
			return;
		}
		if (mRewardSpawnWeight < randomRange(0.f, 1.f))
		{
			return;
		}
		int pick = (int)randomRange(0, mRewardFactories.size());
		if (pick >= 0 && pick < mRewardFactories.size())
		{
			weak<Reward> newReward = mRewardFactories[pick](getWorld());
			newReward.lock()->setActorLocation(getActorLocation());
		}
	}
	void EnemySpaceShip::onActorBeginOverlap(Actor* other)
	{
		SpaceShip::onActorBeginOverlap(other);
		if (isOtherHostile(other))
		{
			other->applyDamage(mCollisionDamage);
		}
	}
	void EnemySpaceShip::setRewardSpawnWeight(float weight)
	{
		if (weight < 0.f || weight > 1.f)
		{
			return;
		}
		mRewardSpawnWeight = weight;
	}

}