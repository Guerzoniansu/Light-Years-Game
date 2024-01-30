#include "widgets/widget.h"

namespace ly
{
	void Widget::NativeDraw(sf::RenderWindow& windowRef)
	{
		if (mIsVisible)
		{
			draw(windowRef);
		}
	}
	bool Widget::handleEvent(const sf::Event& event)
	{
		return false;
	}
	void Widget::setWidgetLocation(const sf::Vector2f& newLoc)
	{
		mWidgetTransform.setPosition(newLoc);
		locationUpdated(newLoc);
	}
	void Widget::setWidgetRotation(float newRot)
	{
		mWidgetTransform.setRotation(newRot);
		rotationUpdated(newRot);
	}
	void Widget::setVisibility(bool newVisibility)
	{
		mIsVisible = newVisibility;
	}
	Widget::Widget()
		:mIsVisible{true},
		mWidgetTransform{}
	{

	}

	void Widget::draw(sf::RenderWindow& windowRef)
	{

	}
	void Widget::locationUpdated(const sf::Vector2f& location)
	{

	}
	void Widget::rotationUpdated(float rotation)
	{

	}

	sf::Vector2f Widget::getCenterPosition() const
	{
		sf::FloatRect bound = getBound();
		return sf::Vector2f{ bound.left + bound.width / 2.f, bound.top + bound.height / 2.f };
	}
}