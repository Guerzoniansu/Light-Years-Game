#pragma once

namespace ly
{
	class Actor;
	class Shooter
	{
	public:
		void shoot();

		virtual bool canShoot() const { return true; };
		virtual bool isOnCoolDown() const { return false; };
		Actor* getOwner() const { return mOwner; }

		int getCurrentLevel() const { return mCurrentLevel; }
		int getMaxLevel() const { return mMaxLevel; }

		virtual void setCurrentLevel(int level);
		virtual void incrementLevel(int amt = 1);
	protected:
		Shooter(Actor* owner);

	private:
		virtual void shootImpl() = 0;
		Actor* mOwner;

		int mCurrentLevel;
		int mMaxLevel;
	};
}