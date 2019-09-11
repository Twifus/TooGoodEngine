cmake_minimum_required(VERSION 3.0)

project(TooGoodEngine
	LANGUAGES CXX C)

## SDL2
if(WIN32) # On Windows systems, search for SDL2 in `external` directory
	set(SDL2_PATH "${CMAKE_SOURCE_DIR}/external/SDL2-2.0.10")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
##

include(CTest)
include_directories("include")

# Game
add_executable(Game src/Game.cpp src/Vector3.cpp include/Vector3.hpp src/Particle.cpp include/Particle.hpp src/Frame.cpp include/Frame.hpp)
target_link_libraries(Game ${SDL2_LIBRARY})
if(WIN32) # On Windows systems, copy SDL2.dll to build directory
	if(CMAKE_SIZEOF_VOID_P EQUAL 8)
		add_custom_command(TARGET Game POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/external/SDL2-2.0.10/lib/x64/SDL2.dll $<TARGET_FILE_DIR:Game>)
	else()
		add_custom_command(TARGET Game POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/external/SDL2-2.0.10/lib/x86/SDL2.dll $<TARGET_FILE_DIR:Game>)
	endif()
endif()

# TestVector3
add_executable(TestVector3 tests/TestVector3.cpp src/Vector3.cpp include/Vector3.hpp)
add_test(Test_Vector3 TestVector3)