#pragma once
#include "gameplay/gamestage.h"
#include "framework/world.h"

namespace ly
{
	class WaitStage : public GameStage
	{
	public:
		WaitStage(World* world, float waitDuration = 5.f);
		virtual void startStage() override;

	private:
		float mWaitDuration;
	};
}