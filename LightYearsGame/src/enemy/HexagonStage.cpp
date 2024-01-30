#include "enemy/HexagonStage.h"
#include "framework/world.h"
#include "enemy/hexagon.h"

namespace ly
{
	HexagonStage::HexagonStage(World* world)
		:GameStage{world},
		mSpawnInterval{5.0f},
		mSideSpawnOffset{80.f},
		mSpawnGroupAmt{5},
		mCurrentSpawnCount{0},
		mMidSpawnLoc{world->getWindowSize().x / 2.f, -25.f },
		mRightSpawnLoc{world->getWindowSize().x / 2.f + mSideSpawnOffset, -25.f - mSideSpawnOffset },
		mLeftSpawnLoc{world->getWindowSize().x / 2.f - mSideSpawnOffset, -25.f - mSideSpawnOffset }
	{

	}
	void HexagonStage::startStage()
	{
		mSpawnTimerHandle = TimerManager::get().setTimer(getWeakRef(), &HexagonStage::spawnHexagon, mSpawnInterval, true);
	}
	void HexagonStage::stageFinished()
	{
		TimerManager::get().clearTimer(mSpawnTimerHandle);
	}
	void HexagonStage::spawnHexagon()
	{
		weak<Hexagon> newHexagon = getWorld()->spawnActor<Hexagon>();
		newHexagon.lock()->setActorLocation(mMidSpawnLoc);

		newHexagon = getWorld()->spawnActor<Hexagon>();
		newHexagon.lock()->setActorLocation(mLeftSpawnLoc);

		newHexagon = getWorld()->spawnActor<Hexagon>();
		newHexagon.lock()->setActorLocation(mRightSpawnLoc);

		if (++mCurrentSpawnCount == mSpawnGroupAmt)
		{
			finishStage();
		}
	}
}