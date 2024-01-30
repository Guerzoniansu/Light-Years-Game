#pragma once
#include <memory>
#include "framework/core.h"
#include "framework/delegate.h"

namespace ly
{
	class Object : public std::enable_shared_from_this<Object>
	{
	public:
		Object();
		virtual ~Object();

		virtual void Destroy();
		bool IsPendingDestroy() const { return mIsPendingDestroy; }

		weak<Object> getWeakRef();
		weak<const Object> getWeakRef() const;
		Delegate<Object*> onDestroy;

		unsigned int getUniqueId() const { return mUniqueID; }

	private:
		bool mIsPendingDestroy;
		unsigned int mUniqueID;

		static unsigned int mUniqueIDCounter;
		static unsigned int getNextAvailableId();
	};
}