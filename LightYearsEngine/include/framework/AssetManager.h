#pragma once
#include "SFML/Graphics.hpp"
#include "framework/core.h"

namespace ly
{
	class AssetManager
	{
	public:
		static AssetManager& Get();
		shared<sf::Texture> LoadTexture(const std::string& path);
		shared<sf::Font> LoadFont(const std::string& path);
		void cleanCycle();
		void setAssetRootDirectory(const std::string& directory);

	protected:
		AssetManager();
	private:
		template<typename T>
		shared<T> loadAsset(const std::string& path, dict<std::string, shared<T>>& container);
		static unique<AssetManager> assetManager;
		dict<std::string, shared<sf::Texture>> mLoadedTextureMap;
		dict<std::string, shared<sf::Font>> mLoadedFontMap;
		std::string mRootDirectory;

		template<typename T>
		void cleanUniqueRef(dict<std::string, shared<T>> container);
	};

	template<typename T>
	shared<T> AssetManager::loadAsset(const std::string& path, dict<std::string, shared<T>>& container)
	{
		auto found = container.find(path);
		if (found != container.end())
		{
			return found->second;
		}
		shared<T> newAsset{ new T };

		if (newAsset->loadFromFile(mRootDirectory + path))
		{
			container.insert({ path, newAsset });
			return newAsset;
		}

		return shared<T> {nullptr};
	}

	template<typename T>
	void AssetManager::cleanUniqueRef(dict<std::string, shared<T>> container)
	{
		for (auto iter = container.begin(); iter != container.end();)
		{
			if (iter->second.unique())
			{
				LOG("Cleaning asset: %s", iter->first.c_str());
				iter = container.erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}
}