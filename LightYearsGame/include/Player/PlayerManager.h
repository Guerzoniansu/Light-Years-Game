#pragma once
#include "framework/core.h"
#include "Player/player.h"

namespace ly
{
	class PlayerManager
	{
	public:
		Player& createNewPlayer();

		Player* getPlayer(int playerIndex = 0);
		const Player* getPlayer(int playerIndex = 0) const;

		static PlayerManager& get();

		void reset();

	protected: //Because we want it to be a singleton class it means only one instance of it will be created
		PlayerManager();
		
	private:
		list<Player> mPlayers;
		static unique<PlayerManager> mPlayerManager;
	};
}