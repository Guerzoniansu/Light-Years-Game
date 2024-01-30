#pragma once
#include <SFML/Graphics.hpp>
#include "framework/core.h"
#include "framework/object.h"
#include "gameplay/gamestage.h"
#include "widgets/HUD.h"

namespace ly
{
	class Actor;
	class Application; //This line tells the program that the owner of World is Application
	class GameStage;
	class  World : public Object
	{
	public:
		 World(Application* owningApp);

		 void BeginPlayInternal();
		 void TickInternal(float deltaTime);

		 void Render(sf::RenderWindow& window);

		 virtual ~World(); //So that it can be overtime by the owner class's destructor

		 template<typename actorType, typename... Args>
		 weak<actorType> spawnActor(Args... args);

		 template<typename hudType, typename... Args>
		 weak<hudType> spawnHUD(Args... args);

		 sf::Vector2u getWindowSize() const;
		 void cleanCycle();
		 void addStage(const shared<GameStage>& newStage);
		 bool DispatchEvent(const sf::Event& event);

		 Application* getApplication() { return mOwningApp; }
		 const Application* getApplication() const { return mOwningApp; }

	private:
		void RenderHUD(sf::RenderWindow& window);
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		Application* mOwningApp;
		bool mBegunPlay;

		list<shared<Actor>> mActors;
		list<shared<Actor>> mPendingActors; //List of the actors we wanna add to the mActors list
		list<shared<GameStage>> mGameStages;

		list<shared<GameStage>>::iterator mCurrentStage;

		shared<HUD> mHUD;

		virtual void initGameStages();
		virtual void AllGameStageFinished();
		void nextGameStage();

		void startStages();
	};

	template<typename actorType, typename... Args>
	weak<actorType> World::spawnActor(Args... args) //Creates a new actor
	{
		shared<actorType> newActor{ new actorType{this, args...} };
		mPendingActors.push_back(newActor);
		return newActor;
	}
	template<typename hudType, typename ...Args>
	inline weak<hudType> World::spawnHUD(Args ...args)
	{
		shared<hudType> newHUD{ new hudType{args...} };
		mHUD = newHUD;
		return newHUD;
	}
}