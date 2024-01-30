#pragma once

#include "framework/object.h"
#include "framework/delegate.h"
#include "framework/world.h"

namespace ly
{
	class World;
	class GameStage : public Object
	{
	public:
		GameStage(World* world);
		const World* getWorld() const { return mWorld; };
		World* getWorld() { return mWorld; };

		Delegate<> onStageFinished;

		virtual void startStage();
		virtual void tickStage(float deltaTime);
		void finishStage();
		bool isStageFinished() const { return mStageFinished; };

	private:
		World* mWorld;
		bool mStageFinished;
		virtual void stageFinished();
	};
}