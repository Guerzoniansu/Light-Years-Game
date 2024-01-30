#pragma once
#include <string>

std::string getResourceDir()
{
#ifdef NDEBUG //Release build
	return "assets/";
#else // NDEBUG //Release build
	return "E:/UdemyCourseonGamedev/ProjectOne/LightYears/LightYearsGame/assets/";
#endif
}
