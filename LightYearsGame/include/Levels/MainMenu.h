#pragma once
#include "framework/world.h"

namespace ly
{
	class MainMenuHUD; //MainMenuHUD is hold by MainMenu as a weak reference
	class MainMenu : public World
	{
	public:
		MainMenu(Application* owningApp);
		virtual void BeginPlay() override;
	private:
		weak<MainMenuHUD> mMainMenuHUD;
		void startGame();
		void quitGame();
	};
}