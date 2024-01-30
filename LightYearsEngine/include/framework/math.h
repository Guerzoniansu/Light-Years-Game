#pragma once
#include <SFML/Graphics.hpp>

#include <cmath>

namespace ly
{
	sf::Vector2f rotationToVector(float rotation);
	float degreesToRadians(float degrees);
	float radiansToDegrees(float radians);

	template<typename T>
	float getVectorLength(const sf::Vector2<T>& vector)
	{
		return std::sqrt(vector.x * vector.x + vector.y * vector.y);
	}
	template<typename T>
	sf::Vector2<T> scaleVector(sf::Vector2<T>& vector, float amt)
	{
		vector.x *= amt;
		vector.y *= amt;
		return vector;
	}
	template<typename T>
	sf::Vector2<T> normalize(sf::Vector2<T>& vector)
	{
		float vectorLength = getVectorLength(vector);
		if (vectorLength == 0.f)
		{
			return sf::Vector2<T>{};
		}
		scaleVector(vector, 1.f / vectorLength);
		return vector;
	}

	sf::Color lerpColor(const sf::Color& a, const sf::Color& b, float alpha);

	sf::Vector2f lerpVector(const sf::Vector2f& a, const sf::Vector2f& b, float alpha);

	float lerpFloat(float a, float b, float alpha);
	float randomRange(float min, float max);
	sf::Vector2f RandomUnitVector();
}