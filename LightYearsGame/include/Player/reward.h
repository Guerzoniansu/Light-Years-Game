#pragma once
#include <functional>
#include "framework/actor.h"
#include "player/playerSpaceship.h"

namespace ly
{
	class PlayerSpaceShip;
	class Reward;
	using RewardFunction = std::function<void(PlayerSpaceShip*)>;
	using rewardFactoryFunc = std::function<weak<Reward>(World*)>;

	class Reward:public Actor
	{
	public:
		Reward(World* world, const std::string& texturePath, RewardFunction rewardFunc, float speed = 200.f);
		virtual void BeginPlay() override;

		virtual void Tick(float deltaTime) override;

	private:
		virtual void onActorBeginOverlap(Actor* actor) override;
		float mSpeed;
		RewardFunction mRewardFunc;
	};

	weak<Reward> createHealthReward(World* world);
	weak<Reward> createThreeWayShooterReward(World* world);
	weak<Reward> createFrontalWiperReward(World* world);
	weak<Reward> createLifeReward(World* world);

	weak<Reward> createReward(World* world, const std::string& texturePath, RewardFunction rewardFunction);

	void rewardHealth(PlayerSpaceShip* player);
	void rewardThreeWayShooter(PlayerSpaceShip* player);
	void rewardFrontalWiper(PlayerSpaceShip* player);
	void rewardLife(PlayerSpaceShip* playerSpaceShip);
}