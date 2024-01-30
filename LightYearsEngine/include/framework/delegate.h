#pragma once
#include <functional>
#include "framework/core.h"

namespace ly
{
	class Object;
	template<typename... Args>
	class Delegate
	{
	public:
		template<typename className>
		void bindAction(weak<Object> obj, void(className::*callback)(Args...))
		{
			std::function<bool(Args...)> callBackFunc = [obj, callback](Args...args)->bool
			{
				if (!obj.expired())
				{
					(static_cast<className*>(obj.lock().get())->*callback)(args...);
					return true;
				}
				return false;
			};

			mCallBacks.push_back(callBackFunc);
		}

		void broadCast(Args... args)
		{
			for (auto iter = mCallBacks.begin(); iter!= mCallBacks.end();)
			{
				if ((*iter)(args...))
				{
					++iter;
				}
				else
				{
					iter = mCallBacks.erase(iter);
				}
			}
		}

	private:
		list<std::function<bool(Args...)>> mCallBacks;
	};
}