#include "enemy/TwinBladeStage.h"
#include "enemy/TwinBlade.h"

namespace ly
{
	TwinBladeStage::TwinBladeStage(World* world)
		:GameStage{world},
		mSpawnInterval{1.5f},
		mSpawnDistanceToCenter{100.f},
		mLeftSpawnLoc{world->getWindowSize().x / 2.f - mSpawnDistanceToCenter, 0.f},
		mRightSpawnLoc{ world->getWindowSize().x / 2.f + mSpawnDistanceToCenter, 0.f },
		mSpawnLoc{mLeftSpawnLoc},
		mSpawnAmt{10},
		mCurrentSpawnCount{0}
	{

	}
	void TwinBladeStage::startStage()
	{
		mSpawnTimerHandle = TimerManager::get().setTimer(getWeakRef(), &TwinBladeStage::spawnTwinBlade, mSpawnInterval, true);
	}
	void TwinBladeStage::spawnTwinBlade()
	{
		weak<TwinBlade> newTwinBlade = getWorld()->spawnActor<TwinBlade>();
		newTwinBlade.lock()->setActorLocation(mSpawnLoc);

		if (mSpawnLoc == mLeftSpawnLoc)
		{
			mSpawnLoc = mRightSpawnLoc;
		}
		else
		{
			mSpawnLoc = mLeftSpawnLoc;
		}

		++mCurrentSpawnCount;
		if (mCurrentSpawnCount == mSpawnAmt)
		{
			finishStage();
			return;
		}
	}
	void TwinBladeStage::stageFinished()
	{
		TimerManager::get().clearTimer(mSpawnTimerHandle);
	}
}