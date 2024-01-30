#include "framework/application.h"
#include "framework/core.h"
#include "framework/world.h"
#include "framework/AssetManager.h"
#include "framework/physics.h"
#include "framework/timer.h"

namespace ly
{
    Application::Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title, sf::Uint32 style)
        :mWindow{ sf::VideoMode(windowWidth, windowHeight), title, style },
        mTargetFrameRate{ 60.f },
        mTickClock{},
        mCurrentWorld{ nullptr },
        mCleanCycleClock{},
        mCleanCycleInterval{2.f}
    {

    }

    Application::~Application()
    {

    }

    void Application::Run()
    {
        //sf::Clock().restart() reset the time and returns the time elapsed since the clock was started
        mTickClock.restart();
        float accumulatedTime = 0.f;
        float targetDeltaTime = 1.f / mTargetFrameRate; //Time to update the game window

        while (mWindow.isOpen()) //Runs until the user closes the window
        {
            sf::Event event;
            while (mWindow.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    quitApplication();
                }
                else
                {
                    DispatchEvent(event);
                }
            }
            float frameDeltaTime = mTickClock.restart().asSeconds();
            accumulatedTime += frameDeltaTime;
            while (accumulatedTime > targetDeltaTime)
            {
                accumulatedTime -= targetDeltaTime;
                TickInternal(targetDeltaTime);
                RenderInternal();
            }
        }
    }

    bool Application::DispatchEvent(const sf::Event& event)
    {
        if (mCurrentWorld)
        {
            return mCurrentWorld->DispatchEvent(event);
        }

        return false;
    }

    sf::Vector2u Application::getWindowSize() const
    {
        return mWindow.getSize();
    }
    void Application::TickInternal(float deltaTime)
    {
        Tick(deltaTime);

        if (mCurrentWorld)
        {
            //mCurrentWorld->BeginPlayInternal();
            mCurrentWorld->TickInternal(deltaTime);
        }

        TimerManager::get().updateTimer(deltaTime);

        Physics::get().step(deltaTime);

        if (mCleanCycleClock.getElapsedTime().asSeconds() >= mCleanCycleInterval)
        {
            mCleanCycleClock.restart();
            AssetManager::Get().cleanCycle();
            if (mCurrentWorld)
            {
                mCurrentWorld->cleanCycle();
            }
        }

        if (mPendingWorld && mPendingWorld != mCurrentWorld)
        {
            mCurrentWorld = mPendingWorld;
            Physics::get().cleanUp();
            mCurrentWorld->BeginPlayInternal();
        }
    }
    void Application::RenderInternal()
    {
        mWindow.clear();
        Render();
        mWindow.display();
    }
    void Application::Render()
    {
        if (mCurrentWorld)
        {
            mCurrentWorld->Render(mWindow);
        }
    }
    void Application::Tick(float deltaTime)
    {
        //LOG("Ticking at frame rate: %f", 1.f / deltaTime);
    }

    void Application::quitApplication()
    {
        mWindow.close();
    }
}