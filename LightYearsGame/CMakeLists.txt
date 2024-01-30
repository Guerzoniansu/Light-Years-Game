add_executable(${LIGHT_YEARS_GAME_TARGET_NAME}
	${CMAKE_CURRENT_SOURCE_DIR}/include/GameFrameWork/GameApplication.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/GameFrameWork/GameApplication.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/SpaceShip/spaceship.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/SpaceShip/spaceship.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/weapon/shooter.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/weapon/shooter.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/weapon/bulletshooter.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/weapon/bulletshooter.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/weapon/bullet.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/weapon/bullet.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/weapon/threeWayShooter.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/weapon/threeWayShooter.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/weapon/FrontalWiper.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/weapon/FrontalWiper.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/gameplay/health.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/gameplay/health.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/Player/playerSpaceship.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/Player/playerSpaceship.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/VFX/explosion.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/VFX/explosion.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/enemy/EnemySpaceShip.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/enemy/EnemySpaceShip.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/enemy/vanguard.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/enemy/vanguard.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/enemy/VanguardStage.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/enemy/VanguardStage.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/enemy/TwinBlade.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/enemy/TwinBlade.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/enemy/TwinBladeStage.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/enemy/TwinBladeStage.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/enemy/hexagon.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/enemy/hexagon.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/enemy/HexagonStage.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/enemy/HexagonStage.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/enemy/ufo.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/enemy/ufo.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/enemy/UfoStage.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/enemy/UfoStage.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/enemy/ChaosStage.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/enemy/ChaosStage.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/enemy/boss.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/enemy/boss.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/enemy/BossStage.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/enemy/BossStage.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/Levels/levelone.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/Levels/levelone.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/Levels/MainMenu.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/Levels/MainMenu.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/Player/reward.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/Player/reward.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/Player/player.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/Player/player.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/Player/PlayerManager.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/Player/PlayerManager.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/widgets/GamePlayHUD.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/widgets/GamePlayHUD.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/widgets/MainMenuHUD.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/widgets/MainMenuHUD.cpp
)

target_include_directories(${LIGHT_YEARS_GAME_TARGET_NAME} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(${LIGHT_YEARS_GAME_TARGET_NAME} PUBLIC ${LIGHT_YEARS_ENGINE_TARGET_NAME})

#Basically, we need a custom command which says that if something is different in the DLL of SFML, then we copy the DLL file
#We need to do this because if we don't, we get an error saying that the executable is not finding the DLLs of the SFML Library
#We are linking the library here staticly (we are copying all the SFML library file to our code base) so we need to add the DLLs to the folder where the executable is
#ACTUALLY, IT IS NOT REALLY NECESSARY BECAUSE WE ARE NOT BUILDING SHARED LIBS but just for security it is better like that

function(copyLibDirToTarget LIB_NAME TARGET_NAME)
	add_custom_command(
	TARGET ${TARGET_NAME}
	POST_BUILD
	COMMAND
	${CMAKE_COMMAND} -E copy_directory #Copy all the directory
	$<TARGET_FILE_DIR:${LIB_NAME}> #Represents what is the build directory, the LightYearsEngine directory here
	$<TARGET_FILE_DIR:${TARGET_NAME}> #We copy it to the LightYearsGame executable
	)
endfunction()

copyLibDirToTarget(${LIGHT_YEARS_ENGINE_TARGET_NAME} ${LIGHT_YEARS_GAME_TARGET_NAME})

set(RESOURCE_FOLDER_NAME "assets")
set(RESOURCE_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${RESOURCE_FOLDER_NAME}")

add_custom_command(
	TARGET ${LIGHT_YEARS_GAME_TARGET_NAME}
	POST_BUILD
	COMMAND
	${CMAKE_COMMAND} -E copy_directory
	${RESOURCE_SRC_DIR}
	$<TARGET_FILE_DIR:${LIGHT_YEARS_GAME_TARGET_NAME}>/${RESOURCE_FOLDER_NAME}

)

configure_file(
	"config.h.in"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/config.h" ESCAPE_QUOTES #ESCAPE_QUOTES means that we are going to replace the variables in config.h.in by their value in CMakeLists.txt
)

