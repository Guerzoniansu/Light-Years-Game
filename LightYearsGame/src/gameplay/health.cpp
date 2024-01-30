#include "gameplay/health.h"
#include "framework/core.h"

namespace ly
{
	Health::Health(float health, float maxhealth)
		: mHealth{ health },
		mMaxHealth{maxhealth}
	{

	}
	void Health::changeHealth(float amt)
	{
		if (amt == 0.f)
		{
			return;
		}
		if (mHealth == 0)
		{
			return;
		}
		mHealth += amt;
		if (mHealth < 0)
		{
			mHealth = 0;
		}
		if (mHealth > mMaxHealth)
		{
			mHealth = mMaxHealth;
		}

		onHealthChanged.broadCast(amt, mHealth, mMaxHealth);

		if (amt < 0)
		{
			takenDamage(-amt);
			if (mHealth <= 0)
			{
				healthEmpty();
			}
		}
	}
	void Health::setInitialHealth(float health, float maxHealth)
	{
		mHealth = health;
		mMaxHealth = maxHealth;
	}
	void Health::takenDamage(float amt)
	{
		onTakenDamage.broadCast(amt, mHealth, mMaxHealth);
	}
	void Health::healthEmpty()
	{
		onHealthEmpty.broadCast();
	}

}