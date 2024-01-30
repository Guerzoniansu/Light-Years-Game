#pragma once
#include "framework/object.h"

#include <SFML/Graphics.hpp>

namespace ly
{
	class HUD : public Object
	{
	public:
		virtual void draw(sf::RenderWindow& windowRef) = 0;
		void nativeInit(const sf::RenderWindow& windowRef);

		bool hasInit() { return mAlreadyInit; }

		virtual bool handleEvent(const sf::Event& event);
		virtual void Tick(float deltaTime);
		
	protected:
		HUD();

	private:
		virtual void init(const sf::RenderWindow& windowRef);
		bool mAlreadyInit;

	};
}