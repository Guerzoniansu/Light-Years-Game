#pragma once
#include<SFML/Graphics.hpp>
#include "core.h"

namespace ly
{
	class World;
	class Application
	{
	public:
		Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title, sf::Uint32 style);
		~Application();
		void Run();

		template <typename worldType>
		weak<worldType> loadWorld();

		sf::Vector2u getWindowSize() const;
		sf::RenderWindow& getWindow() { return mWindow; };
		const sf::RenderWindow& getWindow() const { return mWindow; };

		void quitApplication();

	private:
		bool DispatchEvent(const sf::Event& event);
		void TickInternal(float deltaTime);
		void RenderInternal();

		virtual void Render();
		virtual void Tick(float deltaTime);//Will be overwritten by Tick function of GameApplication

		sf::RenderWindow mWindow;
		float mTargetFrameRate; //Frame rate for the game, similar to number of images per second
		sf::Clock mTickClock; //Ticking time recorder

		shared<World> mCurrentWorld;
		shared<World> mPendingWorld;

		sf::Clock mCleanCycleClock;
		float mCleanCycleInterval;
	};

	template<typename worldType>
	weak<worldType> Application::loadWorld()
	{
		shared<worldType> newWorld{ new worldType{this} };
		mPendingWorld = newWorld;
		return newWorld;
	}
}