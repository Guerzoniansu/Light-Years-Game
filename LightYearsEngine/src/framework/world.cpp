#include "framework/world.h"
#include "framework/core.h"
#include "framework/actor.h"
#include "framework/application.h"
#include "gameplay/gamestage.h"
#include "widgets/HUD.h"

namespace ly
{
	World::World(Application* owningApp)
		:mOwningApp{ owningApp },
		mBegunPlay{ false },
		mActors{},
		mPendingActors{},
		mGameStages{},
		mCurrentStage{mGameStages.end()}
	{
		
	}
	void World::BeginPlayInternal()
	{
		if (!mBegunPlay)
		{
			mBegunPlay = true;
			BeginPlay();
			initGameStages();
			startStages();
		}
	}
	void World::TickInternal(float deltaTime)
	{
		for (shared<Actor> actor : mPendingActors)
		{
			mActors.push_back(actor);
			actor->BeginPlayInternal();
		}
		mPendingActors.clear();

		for (auto iter = mActors.begin(); iter != mActors.end();)
		{
			iter->get()->TickInternal(deltaTime);
			++iter;
		}

		if (mCurrentStage != mGameStages.end())
		{
			mCurrentStage->get()->tickStage(deltaTime);
		}

		Tick(deltaTime);

		if (mHUD)
		{
			if (!mHUD->hasInit())
			{
				mHUD->nativeInit(mOwningApp->getWindow());
			}
			mHUD->Tick(deltaTime);
		}
	}
	void World::Render(sf::RenderWindow& window)
	{
		for (auto actor: mActors)
		{
			actor->Render(window);
		}

		RenderHUD(window);
	}
	World::~World()
	{

	}
	bool World::DispatchEvent(const sf::Event& event)
	{
		if (mHUD)
		{
			return mHUD->handleEvent(event);
		}

		return false;
	}
	void World::RenderHUD(sf::RenderWindow& window)
	{
		if (mHUD)
		{
			mHUD->draw(window);
		}
	}
	void World::BeginPlay()
	{
		
	}

	void World::Tick(float deltaTime)
	{
		
	}

	void World::initGameStages()
	{

	}

	void World::AllGameStageFinished()
	{
		LOG("All stages finished...");
	}
	void World::nextGameStage()
	{
		mCurrentStage = mGameStages.erase(mCurrentStage);
		if (mCurrentStage != mGameStages.end())
		{
			mCurrentStage->get()->startStage();
			mCurrentStage->get()->onStageFinished.bindAction(getWeakRef(), &World::nextGameStage);
		}
		else
		{
			AllGameStageFinished();
		}
	}
	void World::startStages()
	{
		mCurrentStage = mGameStages.begin();
		if (mCurrentStage != mGameStages.end())
		{
			mCurrentStage->get()->startStage();
			mCurrentStage->get()->onStageFinished.bindAction(getWeakRef(), &World::nextGameStage);
		}
		
	}
	sf::Vector2u World::getWindowSize() const
	{
		return mOwningApp->getWindowSize();
	}
	void World::cleanCycle()
	{
		for (auto iter = mActors.begin(); iter != mActors.end();)
		{
			if (iter->get()->IsPendingDestroy())
			{
				iter = mActors.erase(iter); //Remove the iter element from the list and returns the next iterator
			}
			else
			{
				++iter;
			}
		}

		/*for (auto iter = mGameStages.begin(); iter != mGameStages.end(); )
		{
			if (iter->get()->isStageFinished())
			{
				iter = mGameStages.erase(iter);
			}
			else
			{
				++iter;
			}
		}*/
	}
	void World::addStage(const shared<GameStage>& newStage)
	{
		mGameStages.push_back(newStage);
	}
}