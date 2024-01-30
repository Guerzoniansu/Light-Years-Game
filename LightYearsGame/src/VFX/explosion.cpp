#include "VFX/explosion.h"
#include "framework/math.h"
#include "VFX/particle.h"
#include "framework/world.h"

namespace ly
{
	Explosion::Explosion(int particleAmt, float lifeTimeMin, float lifeTimeMax, float sizeMin, float sizeMax, float speedMin, float speedMax, const sf::Color& particleColor, const list<std::string>& particleImagePaths)
		:mParticleAmt{ particleAmt },
		mLifeTimeMin{lifeTimeMin},
		mLifeTimeMax{ lifeTimeMax },
		mSizeMin{sizeMin},
		mSizeMax{sizeMax},
		mSpeedMin{speedMin},
		mSpeedMax{speedMax},
		mParticleColor{particleColor},
		mParticleImagePaths{particleImagePaths}
	{
	}
	void Explosion::spawnExplosion(World* world, const sf::Vector2f& location)
	{
		if (!world)
		{
			return;
		}
		for (int i = 0; i < mParticleAmt; ++i)
		{
			std::string particleImagePath = mParticleImagePaths[(int)randomRange(0, mParticleImagePaths.size())];
			weak<Particle> newParticle = world->spawnActor<Particle>(particleImagePath);
			newParticle.lock()->RandomLifeTime(mLifeTimeMin, mLifeTimeMax);
			newParticle.lock()->setActorLocation(location);
			newParticle.lock()->RandomSize(mSizeMin, mSizeMax);
			newParticle.lock()->RandomVelocity(mSpeedMin, mSpeedMax);
			newParticle.lock()->getSprite().setColor(mParticleColor);
		}
	}
}