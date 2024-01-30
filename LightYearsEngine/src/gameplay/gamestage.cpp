#include "gameplay/gamestage.h"

namespace ly
{
	GameStage::GameStage(World* world)
		: mWorld {world},
		mStageFinished{false}
	{

	}
	void GameStage::startStage()
	{
		LOG("Stage started..");
	}
	void GameStage::tickStage(float deltaTime)
	{
		
	}
	void GameStage::finishStage()
	{
		mStageFinished = true;
		stageFinished();
		onStageFinished.broadCast();
	}
	void GameStage::stageFinished()
	{
		LOG("Stage finished...");
	}
}