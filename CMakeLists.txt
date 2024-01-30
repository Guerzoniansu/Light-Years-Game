cmake_minimum_required(VERSION 3.27.8)
set(CMAKE_BUILD_TYPE "Debug")

project(LightYears
	VERSION 1.0.0
	LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#Creates a variable
set(LIGHT_YEARS_ENGINE_TARGET_NAME LightYearsEngine)
set(LIGHT_YEARS_GAME_TARGET_NAME LightYearsGame)

add_subdirectory(LightYearsEngine) #This tells CMake to go and look in the LightYears folder if there is a CMakeLists.txt file
add_subdirectory(LightYearsGame)