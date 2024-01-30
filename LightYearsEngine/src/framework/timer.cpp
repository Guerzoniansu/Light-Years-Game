#include "framework/timer.h"

namespace ly
{
	unsigned int TimerHandle::timerKeyCounter = 0;

	TimerHandle::TimerHandle()
		:mTimerKey {getNextTimerKey()}
	{

	}

	bool operator == (const TimerHandle& lhs, const TimerHandle& rhs)
	{
		return lhs.getTimerKey() == rhs.getTimerKey();
	}

	Timer::Timer(weak<Object> weakRef, std::function<void()> callback, float duration, bool repeat)
		: mListener{weakRef, callback},
		mDuration{duration},
		mRepeat {repeat},
		mTimeCounter{0.f},
		mIsExpired{false}
	{

	}
	void Timer::tickTime(float deltaTime)
	{
		if (expired())
		{
			return;
		}
		
		mTimeCounter += deltaTime;
		if (mTimeCounter >= mDuration)
		{
			mListener.second();

			if (mRepeat)
			{
				mTimeCounter = 0.f;
			}
			else
			{
				setExpired();
			}
		}
	}
	bool Timer::expired() const
	{
		return mIsExpired || mListener.first.expired() || mListener.first.lock()->IsPendingDestroy();
	}
	void Timer::setExpired()
	{
		mIsExpired = true;
	}
	
	unique<TimerManager> TimerManager::timerManager{ nullptr };

	void TimerManager::updateTimer(float deltaTime)
	{
		for (auto iter = mTimers.begin(); iter != mTimers.end(); )
		{
			if (iter->second.expired())
			{
				iter = mTimers.erase(iter);
			}
			else
			{
				iter->second.tickTime(deltaTime);
				++iter;
			}
		}
	}

	void TimerManager::clearTimer(TimerHandle timerHandle)
	{
		auto iter = mTimers.find(timerHandle);
		if (iter != mTimers.end())
		{
			iter->second.setExpired();
		}
	}

	TimerManager::TimerManager()
		: mTimers{}
	{

	}

	TimerManager& TimerManager::get()
	{
		if (!timerManager)
		{
			timerManager = std::move(unique<TimerManager>(new TimerManager{}));
		}

		return *timerManager;
	}
}