#pragma once
#include "framework/delegate.h"

namespace ly
{
	class Health
	{
	public:
		Health(float health, float maxhealth);
		void changeHealth(float amt);
		void setInitialHealth(float health, float maxHealth);
		float getHealth() const { return mHealth; }
		float getMaxHealth() const { return mMaxHealth; }

		Delegate<float, float, float> onHealthChanged;
		Delegate<float, float, float> onTakenDamage;
		Delegate<> onHealthEmpty;

	private:
		void takenDamage(float amt);
		void healthEmpty();
		float mHealth;
		float mMaxHealth;
	};
}