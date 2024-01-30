add_library(${LIGHT_YEARS_ENGINE_TARGET_NAME} STATIC
	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/application.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/application.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/math.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/math.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/object.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/object.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/AssetManager.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/AssetManager.cpp
	
	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/actor.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/actor.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/core.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/core.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/world.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/world.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/EntryPoint.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/EntryPoint.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/physics.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/physics.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/delegate.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/delegate.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/timer.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/timer.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/BackDropActor.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/BackDropActor.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/BackGroundLayer.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/BackGroundLayer.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/VFX/particle.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/VFX/particle.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/gameplay/gamestage.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/gameplay/gamestage.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/gameplay/waitstage.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/gameplay/waitstage.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/widgets/HUD.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/widgets/HUD.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/widgets/widget.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/widgets/widget.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/widgets/TextWidget.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/widgets/TextWidget.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/widgets/ImageWidget.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/widgets/ImageWidget.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/widgets/guage.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/widgets/guage.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/widgets/button.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/widgets/button.cpp
)

target_include_directories(${LIGHT_YEARS_ENGINE_TARGET_NAME} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/src
)

include(FetchContent)
set(SFML_LIB_NAME SFML)

FetchContent_Declare(
	${SFML_LIB_NAME}
	GIT_REPOSITORY https://github.com/SFML/SFML
	GIT_TAG 2.6.0
	GIT_SHALLOW FALSE
)

FetchContent_MakeAvailable(${SFML_LIB_NAME})

target_link_libraries(${LIGHT_YEARS_ENGINE_TARGET_NAME} PUBLIC sfml-graphics)
target_link_libraries(${LIGHT_YEARS_ENGINE_TARGET_NAME} PUBLIC sfml-audio)
target_link_libraries(${LIGHT_YEARS_ENGINE_TARGET_NAME} PUBLIC sfml-system)
target_link_libraries(${LIGHT_YEARS_ENGINE_TARGET_NAME} PUBLIC sfml-window)

set(BOX2D_LIB_NAME Box2D)
FetchContent_Declare(
	${BOX2D_LIB_NAME}
	GIT_REPOSITORY https://github.com/erincatto/box2d
	GIT_TAG v2.4.1
	GIT_SHALLOW FALSE
)

FetchContent_MakeAvailable(${BOX2D_LIB_NAME})

target_link_libraries(${LIGHT_YEARS_ENGINE_TARGET_NAME} PUBLIC box2d)

#Basically, we need a custom command which says that if something is different in the DLL of SFML, then we copy the DLL file
#We need to do this because if we don't, we get an error saying that the executable is not finding the DLLs of the SFML Library
#We are linking the library here staticly (we are copying all the SFML library file to our code base) so we need to add the DLLs to the folder where the executable is
#ACTUALLY, IT IS NOT REALLY NECESSARY BECAUSE WE ARE NOT BUILDING SHARED LIBS but just for security it is better like that

function(copyLibToTarget LIB_NAME TARGET_NAME)
	add_custom_command(
	TARGET ${TARGET_NAME}
	POST_BUILD
	COMMAND
	${CMAKE_COMMAND} -E copy_if_different #States for something is different
	$<TARGET_FILE:${LIB_NAME}> #Represents what is the build file, the DLL file here
	$<TARGET_FILE_DIR:${TARGET_NAME}> #We copy it to the LightYearsGame executable
	)
endfunction()

copyLibToTarget(sfml-graphics ${LIGHT_YEARS_ENGINE_TARGET_NAME})
copyLibToTarget(sfml-audio ${LIGHT_YEARS_ENGINE_TARGET_NAME})
copyLibToTarget(sfml-system ${LIGHT_YEARS_ENGINE_TARGET_NAME})
copyLibToTarget(sfml-window ${LIGHT_YEARS_ENGINE_TARGET_NAME})
copyLibToTarget(box2d ${LIGHT_YEARS_ENGINE_TARGET_NAME})