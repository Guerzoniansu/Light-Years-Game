#include "gameplay/waitstage.h"
#include "framework/timer.h"

namespace ly
{
	WaitStage::WaitStage(World* world, float waitDuration)
		:GameStage{world},
		mWaitDuration{waitDuration}
	{

	}
	void WaitStage::startStage()
	{
		TimerManager::get().setTimer(getWeakRef(), &WaitStage::finishStage, mWaitDuration);
	}
}