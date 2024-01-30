#pragma once
#include "framework/core.h"
#include "framework/object.h"
#include <functional>

namespace ly
{
	struct TimerHandle
	{
	public:
		TimerHandle();
		unsigned int getTimerKey() const { return mTimerKey; };
	private:
		unsigned int mTimerKey;
		static unsigned int timerKeyCounter;
		static unsigned int getNextTimerKey() { return ++timerKeyCounter; };

	};

	struct TimerHandleHashFunction
	{
	public:
	public:
		std::size_t operator()(const TimerHandle& timerHandle) const
		{
			return timerHandle.getTimerKey();
		}
	};

	bool operator==(const TimerHandle& lhs, const TimerHandle& rhs);

	struct Timer
	{
	public:
		Timer(weak<Object> weakRef, std::function<void()> callback, float duration, bool repeat);
		void tickTime(float deltaTime);
		bool expired() const;
		void setExpired();
	private:
		std::pair<weak<Object>, std::function<void()>> mListener;
		float mDuration;
		bool mRepeat;
		float mTimeCounter;
		bool mIsExpired;
	};

	class TimerManager
	{
	public:
		static TimerManager& get();
		template<typename className>
		TimerHandle setTimer(weak<Object> weakRef, void(className::* callback)(), float duration, bool repeat = false)
		{
			TimerHandle newHandle{};
			mTimers.insert({ newHandle, Timer(weakRef, [=] {(static_cast<className*>(weakRef.lock().get())->*callback)(); }, duration, repeat) });
			return newHandle;
		}

		void updateTimer(float deltaTime);
		void clearTimer(TimerHandle timerHandle);

	protected:
		TimerManager();
	private:
		static unique<TimerManager> timerManager;
		dict<TimerHandle, Timer, TimerHandleHashFunction> mTimers;
	};
}