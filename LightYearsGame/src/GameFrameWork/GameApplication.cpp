#include "GameFrameWork/GameApplication.h"
#include "Levels/levelone.h"
#include "Levels/MainMenu.h"
#include "framework/AssetManager.h"
#include "config.h"

ly::Application* GetApplication()
{
	return new ly::GameApplication{};
}

namespace ly
{
	GameApplication::GameApplication()
		: Application{500, 700, "Light Years", sf::Style::Titlebar | sf::Style::Close}
	{
		AssetManager::Get().setAssetRootDirectory(getResourceDir());
		weak<MainMenu> newWorld = loadWorld<MainMenu>();
	}
}

