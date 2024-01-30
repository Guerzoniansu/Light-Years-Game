#include <memory>

#include "framework/object.h"
#include "framework/core.h"

//Parent of Actor class: It contains the destoys function for the classes
namespace ly
{
	unsigned int Object::mUniqueIDCounter = 0;
	Object::Object()
		:mIsPendingDestroy{false},
		mUniqueID{getNextAvailableId()}
	{

	}
	Object::~Object()
	{
		LOG("Object destroyed");
	}
	void Object::Destroy()
	{
		onDestroy.broadCast(this);
		mIsPendingDestroy = true;
	}
	weak<Object> Object::getWeakRef()
	{
		return weak_from_this();
	}
	weak<const Object> Object::getWeakRef() const
	{
		return weak_from_this();
	}
	unsigned int Object::getNextAvailableId()
	{
		return mUniqueIDCounter++;
	}
}