cmake_minimum_required(VERSION 3.0)

project(TooGoodEngine
	LANGUAGES CXX C)

## SDL2
if(WIN32) # On Windows systems, search for SDL2 in `external` directory
	set(SDL2_PATH "${CMAKE_SOURCE_DIR}/external/SDL2-2.0.10")
	set(SDL2_IMAGE_PATH "${CMAKE_SOURCE_DIR}/external/SDL2_image-2.0.5")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

find_package(SDL2_IMAGE REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
##

include(CTest)
include_directories("include")

# Game
add_executable(Game src/Game.cpp
			   src/Vector3.cpp  include/Vector3.hpp
			   src/Particle.cpp include/Particle.hpp
			   src/ForcesRegistery.cpp include/ForcesRegistery.hpp
			   include/ParticleForceGenerator.hpp
			   src/GravityForceGenerator.cpp include/GravityForceGenerator.hpp
			   src/DragForceGenerator.cpp include/DragForceGenerator.hpp
			   src/SpringForceGenerator.cpp include/SpringForceGenerator.hpp
			   src/BungeeSpringForceGenerator.cpp include/BungeeSpringForceGenerator.hpp
			   src/AnchoredSpringForceGenerator.cpp include/AnchoredSpringForceGenerator.hpp
			   src/BuoyancyForceGenerator.cpp include/BuoyancyForceGenerator.hpp
			   src/StiffSpringForceGenerator.cpp include/StiffSpringForceGenerator.hpp
			   src/ParticleContact.cpp include/ParticleContact.hpp
			   include/ParticleContactGenerator.hpp
			   src/LinkContactGenerator.cpp include/LinkContactGenerator.hpp
			   src/Frame.cpp    include/Frame.hpp
			   src/Sprite.cpp   include/Sprite.hpp
		       src/Blob.cpp 	include/Blob.hpp)

target_link_libraries(Game ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})

if(WIN32) # On Windows systems, copy SDL2.dll to build directory
	if(CMAKE_SIZEOF_VOID_P EQUAL 8)
		SET(ARCH_PATH "x64")
	else()
		SET(ARCH_PATH "x86")
	endif()
	add_custom_command(TARGET Game POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/external/SDL2-2.0.10/lib/${ARCH_PATH}/SDL2.dll $<TARGET_FILE_DIR:Game>)
	add_custom_command(TARGET Game POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/external/SDL2_image-2.0.5/lib/${ARCH_PATH}/libjpeg-9.dll $<TARGET_FILE_DIR:Game>)
	add_custom_command(TARGET Game POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/external/SDL2_image-2.0.5/lib/${ARCH_PATH}/libpng16-16.dll $<TARGET_FILE_DIR:Game>)
	add_custom_command(TARGET Game POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/external/SDL2_image-2.0.5/lib/${ARCH_PATH}/libtiff-5.dll $<TARGET_FILE_DIR:Game>)
	add_custom_command(TARGET Game POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/external/SDL2_image-2.0.5/lib/${ARCH_PATH}/libwebp-7.dll $<TARGET_FILE_DIR:Game>)
	add_custom_command(TARGET Game POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/external/SDL2_image-2.0.5/lib/${ARCH_PATH}/zlib1.dll $<TARGET_FILE_DIR:Game>)
	add_custom_command(TARGET Game POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/external/SDL2_image-2.0.5/lib/${ARCH_PATH}/SDL2_image.dll $<TARGET_FILE_DIR:Game>)
endif()

# TestVector3
add_executable(TestVector3 tests/TestVector3.cpp src/Vector3.cpp include/Vector3.hpp)
add_test(Test_Vector3 TestVector3)