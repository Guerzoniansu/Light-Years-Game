#include "enemy/VanguardStage.h"
#include "framework/world.h"
#include "enemy/vanguard.h"
#include "weapon/bulletshooter.h"

namespace ly
{
	VanguardStage::VanguardStage(World* world)
		: GameStage{ world },
		mSpawnInterval{ 1.5f },
		mSwitchInterval{ 5.f },
		mSpawnDistanceToEdge{ 100.f },
		mLeftSpawnLoc{ 0.0f, 0.0f },
		mRightSpawnLoc{ 0.0f, 0.0f },
		mSpawnLoc{ 0.0f, 0.0f },
		mRowsToSpawn{ 2 },
		mRowSpawnCount{ 0 },
		mVanguardsPerRow{5},
		mCurrentRowVanguardCount{0}
	{

	}
	void VanguardStage::startStage()
	{
		auto windowSize = getWorld()->getWindowSize();
		mLeftSpawnLoc = sf::Vector2f{ mSpawnDistanceToEdge, -25.f };
		mRightSpawnLoc = sf::Vector2f{ windowSize.x - mSpawnDistanceToEdge, -25.f };

		switchRow();
	}
	void VanguardStage::stageFinished()
	{
		TimerManager::get().clearTimer(mSpawnTimerHandle);
		TimerManager::get().clearTimer(mSwitchTimerHandle);
	}
	void VanguardStage::spawnVanguard()
	{
		weak<Vanguard> newVanguard = getWorld()->spawnActor<Vanguard>();
		newVanguard.lock()->setActorLocation(mSpawnLoc);

		++mCurrentRowVanguardCount;
		if (mCurrentRowVanguardCount == mVanguardsPerRow)
		{
			TimerManager::get().clearTimer(mSpawnTimerHandle);
			mSwitchTimerHandle = TimerManager::get().setTimer(getWeakRef(), &VanguardStage::switchRow, mSwitchInterval, false);
			mCurrentRowVanguardCount = 0;
		}
	}
	void VanguardStage::switchRow()
	{
		if (mRowSpawnCount == mRowsToSpawn)
		{
			finishStage();
			return;
		}
		if (mSpawnLoc == mLeftSpawnLoc)
		{
			mSpawnLoc = mRightSpawnLoc;
		}
		else
		{
			mSpawnLoc = mLeftSpawnLoc;
		}

		mSpawnTimerHandle = TimerManager::get().setTimer(getWeakRef(), &VanguardStage::spawnVanguard, mSpawnInterval, true);
		
		++mRowSpawnCount;
	}
}