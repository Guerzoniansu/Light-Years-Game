#include "framework/AssetManager.h"

namespace ly
{
	unique<AssetManager> AssetManager::assetManager{ nullptr };
	AssetManager& AssetManager::Get()
	{
		if (!assetManager)
		{
			assetManager = unique<AssetManager>{new AssetManager};
		}
		return *assetManager;
	}
	shared<sf::Texture> AssetManager::LoadTexture(const std::string& path)
	{
		return loadAsset(path, mLoadedTextureMap);
	}

	shared<sf::Font> AssetManager::LoadFont(const std::string& path)
	{
		return loadAsset(path, mLoadedFontMap);
	}

	void AssetManager::cleanCycle()
	{
		cleanUniqueRef<sf::Texture>(mLoadedTextureMap);
		cleanUniqueRef<sf::Font>(mLoadedFontMap);
	}
	void AssetManager::setAssetRootDirectory(const std::string& directory)
	{
		mRootDirectory = directory;
	}
	AssetManager::AssetManager()
		:mRootDirectory{}
	{
		
	}
}