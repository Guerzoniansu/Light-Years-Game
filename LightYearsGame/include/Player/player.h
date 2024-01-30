#pragma once

#include "framework/object.h"
#include "framework/delegate.h"
#include "Player/playerSpaceship.h"
#include "framework/world.h"

namespace ly
{
	class PlayerSpaceShip;
	class World;
	class Player : public Object
	{
	public:
		Player();
		weak<PlayerSpaceShip> spawnSpaceShip(World* world);
		const weak<PlayerSpaceShip> getCurrentSpaceShip() const { return mCurrentPlayerSpaceShip; };

		void addLifeCount(unsigned int count);
		unsigned int getLifeCount() { return mLifeCount; }

		void addScore(unsigned int amt);
		unsigned int getScore() const { return mScore; }

		Delegate<int> onLifeChange;
		Delegate<int> onScoreChange;
		Delegate<> onLifeExhausted;

	private:
		unsigned int mLifeCount;
		unsigned int mScore;
		weak<PlayerSpaceShip> mCurrentPlayerSpaceShip;
	};
}