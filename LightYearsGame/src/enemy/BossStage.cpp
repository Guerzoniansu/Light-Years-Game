#include "enemy/BossStage.h"
#include "enemy/boss.h"
#include "framework/world.h"
#include "framework/actor.h"
#include "weapon/bulletshooter.h"

namespace ly
{
	BossStage::BossStage(World* world)
		:GameStage{world}
	{

	}
	void BossStage::startStage()
	{
		weak<Boss> boss = getWorld()->spawnActor<Boss>();
		auto windowSize = getWorld()->getWindowSize();

		boss.lock()->setActorLocation({ windowSize.x / 2.f, 200.f });

		boss.lock()->onActorDestroy.bindAction(getWeakRef(), &BossStage::BossDestroyed);
	}
	void BossStage::BossDestroyed(Actor* bossActor)
	{
		finishStage();
	}
}