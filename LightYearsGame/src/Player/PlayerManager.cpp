#include "Player/PlayerManager.h"

namespace ly
{
	unique<PlayerManager> PlayerManager::mPlayerManager{nullptr};
	PlayerManager::PlayerManager()
	{
	}
	Player& PlayerManager::createNewPlayer()
	{
		mPlayers.emplace(mPlayers.begin(), Player());
		return mPlayers.back();
	}
	Player* PlayerManager::getPlayer(int playerIndex)
	{
		if (playerIndex >= 0 && playerIndex <= mPlayers.size() - 1)
		{
			return &(mPlayers[playerIndex]);
		}

		return nullptr;
	}
	const Player* PlayerManager::getPlayer(int playerIndex) const
	{
		if (playerIndex >=0 && playerIndex <= mPlayers.size() - 1)
		{
			return &(mPlayers[playerIndex]);
		}

		return nullptr;
	}
	PlayerManager& PlayerManager::get()
	{
		if (!mPlayerManager)
		{
			mPlayerManager = std::move(unique<PlayerManager>{new PlayerManager{}});
		}

		return *mPlayerManager;
	}

	void PlayerManager::reset()
	{
		mPlayers.clear();
	}
}