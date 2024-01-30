#pragma once
#include <SFML/Graphics.hpp>

#include "framework/object.h"

namespace ly
{
	class Widget : public Object
	{
	public:
		void NativeDraw(sf::RenderWindow& windowRef);
		virtual bool handleEvent(const sf::Event& event);
		void setWidgetLocation(const sf::Vector2f& newLoc);
		void setWidgetRotation(float newRot);
		sf::Vector2f getWidgetLocation() { return mWidgetTransform.getPosition(); }
		float getWidgetRotation() { return mWidgetTransform.getRotation(); }

		void setVisibility(bool newVisibility);
		bool getVisibility() const { return mIsVisible; }

		virtual sf::FloatRect getBound() const = 0;
		sf::Vector2f getCenterPosition() const;

	protected:
		Widget();

	private:
		virtual void draw(sf::RenderWindow& windowRef);
		virtual void locationUpdated(const sf::Vector2f& location);
		virtual void rotationUpdated(float rotation);

		sf::Transformable mWidgetTransform;
		bool mIsVisible;
	};
}