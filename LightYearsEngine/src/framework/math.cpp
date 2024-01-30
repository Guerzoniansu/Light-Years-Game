#include "framework/math.h"
#include <cmath>
#include <random>

namespace ly
{
	const float pi = 3.141589;
	sf::Vector2f rotationToVector(float rotation)
	{
		float radians = degreesToRadians(rotation);
		return sf::Vector2f(-std::sin(radians), std::cos(radians));
	}
	float degreesToRadians(float degrees)
	{
		return degrees * (pi / 180.f);
	}
	float radiansToDegrees(float radians)
	{
		return radians * (180.f / pi);
	}
	sf::Color lerpColor(const sf::Color& a, const sf::Color& b, float alpha)
	{
		int lerpR = lerpFloat(a.r, b.r, alpha);
		int lerpG = lerpFloat(a.g, b.g, alpha);
		int lerpB = lerpFloat(a.b, b.b, alpha);
		int lerpA = lerpFloat(a.a, b.a, alpha);

		return sf::Color(lerpR, lerpG, lerpB, lerpA);
	}
	sf::Vector2f lerpVector(const sf::Vector2f& a, const sf::Vector2f& b, float alpha)
	{
		float lerpX = lerpFloat(a.x, b.x, alpha);
		float lerpY = lerpFloat(a.y, b.y, alpha);

		return sf::Vector2f(lerpX, lerpY);
	}
	float lerpFloat(float a, float b, float alpha)
	{
		if (alpha > 1.f)
		{
			alpha = 1.f;
		}
		if (alpha < 0.f)
		{
			alpha = 0.f;
		}
		return a + (b - a) * alpha;
	}

	float randomRange(float min, float max)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<float> distribution{ min, max };

		return distribution(gen);
	}
	sf::Vector2f RandomUnitVector()
	{
		float randomX = randomRange(-1.f, 1.f);
		float randomY = randomRange(-1.f, 1.f);

		sf::Vector2f randVec{ randomX, randomY };
		normalize(randVec);
		return randVec;
	}
}