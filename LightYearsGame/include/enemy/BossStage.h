#pragma once
#include "gameplay/gamestage.h"
#include "framework/world.h"

namespace ly
{
	class BossStage : public GameStage
	{
	public:
		BossStage(World* world);
		virtual void startStage() override;

	private:
		void BossDestroyed(Actor* bossActor);
	};
}