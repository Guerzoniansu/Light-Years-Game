#include "Player/reward.h"
#include "Player/playerSpaceship.h"
#include "weapon/threeWayShooter.h"
#include "weapon/FrontalWiper.h"
#include "framework/world.h"
#include "Player/PlayerManager.h"

namespace ly
{
	Reward::Reward(World* world, const std::string& texturePath, RewardFunction rewardFunc, float speed)
		: Actor{world, texturePath},
		mRewardFunc{rewardFunc},
		mSpeed{speed}
	{

	}
	void Reward::BeginPlay()
	{
		Actor::BeginPlay();
		setEnablePhysics(true);
	}

	void Reward::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		addActorLocationOffset({ 0.f, mSpeed * deltaTime });
	}

	void Reward::onActorBeginOverlap(Actor* actor)
	{
		if (!actor || actor->IsPendingDestroy())
		{
			return;
		}
		if (!PlayerManager::get().getPlayer())
		{
			return;
		}
		weak<PlayerSpaceShip> playerSpaceShip = PlayerManager::get().getPlayer()->getCurrentSpaceShip();
		if (playerSpaceShip.expired() || playerSpaceShip.lock()->IsPendingDestroy())
		{
			return;
		}

		if (playerSpaceShip.lock()->getUniqueId() == actor->getUniqueId())
		{
			mRewardFunc(playerSpaceShip.lock().get());
			Destroy();
		}
	}

	weak<Reward> createHealthReward(World* world)
	{
		return createReward(world, "SpaceShooterRedux/PNG/Power-ups/pill_green.png", rewardHealth);
	}

	weak<Reward> createThreeWayShooterReward(World* world)
	{
		return createReward(world, "SpaceShooterRedux/PNG/Power-ups/bolt_bronze.png", rewardThreeWayShooter);
	}

	weak<Reward> createFrontalWiperReward(World* world)
	{
		return createReward(world, "SpaceShooterRedux/PNG/Power-ups/bold_silver.png", rewardFrontalWiper);
	}

	weak<Reward> createLifeReward(World* world)
	{
		return createReward(world, "SpaceShooterRedux/PNG/UI/playerLife1_blue.png", rewardLife);
	}

	weak<Reward> createReward(World* world, const std::string& texturePath, RewardFunction rewardFunction)
	{
		weak<Reward> reward = world->spawnActor<Reward>(texturePath, rewardFunction);
		return reward;
	}

	void rewardHealth(PlayerSpaceShip* player)
	{
		static float rewardAmt = 10.f;
		if (player && !player->IsPendingDestroy())
		{
			player->getHealthComp().changeHealth(rewardAmt);
		}
	}

	void rewardThreeWayShooter(PlayerSpaceShip* player)
	{
		if (player && !player->IsPendingDestroy())
		{
			player->setShooter(unique<Shooter>{new ThreeWayShooter{ player, 0.3f, {50.f, 0.f} }});
		}
	}

	void rewardFrontalWiper(PlayerSpaceShip* player)
	{
		if (player && !player->IsPendingDestroy())
		{
			player->setShooter(unique<Shooter>{new FrontalWiper{ player, 0.4f, {50.f, 0.f} }});
		}
	}

	void rewardLife(PlayerSpaceShip* playerSpaceShip)
	{
		if (playerSpaceShip && !playerSpaceShip->IsPendingDestroy())
		{
			Player* player = PlayerManager::get().getPlayer();
			if (player)
			{
				player->addLifeCount(1);
			}
		}
	}
}