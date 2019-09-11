cmake_minimum_required(VERSION 3.0)

project(TooGoodEngine
	LANGUAGES CXX C)

# SDL2
if(WIN32)
	set(SDL2_PATH "${CMAKE_SOURCE_DIR}/external/SDL2-2.0.10")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})
#

include(CTest)
include_directories("include")

add_executable(TestSDL tests/TestSDL.cpp src/Vector3.cpp include/Vector3.hpp src/Particle.cpp include/Particle.hpp src/Frame.cpp include/Frame.hpp)
target_link_libraries(TestSDL ${SDL2_LIBRARY})
if(WIN32)
	if(CMAKE_SIZEOF_VOID_P EQUAL 8)
		add_custom_command(TARGET TestSDL POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/external/SDL2-2.0.10/lib/x64/SDL2.dll $<TARGET_FILE_DIR:TestSDL>)
	else()
		add_custom_command(TARGET TestSDL POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/external/SDL2-2.0.10/lib/x86/SDL2.dll $<TARGET_FILE_DIR:TestSDL>)
	endif()
endif()

add_executable(Game src/Game.cpp src/Frame.cpp include/Frame.hpp src/Particle.cpp include/Particle.hpp src/Vector3.cpp include/Vector3.hpp)

add_executable(TestVector3 tests/TestVector3.cpp src/Vector3.cpp include/Vector3.hpp)
add_test(TestVector3 COMMAND "TestVector3")

# target_link_libraries(target ${SDL2_LIBRARY})