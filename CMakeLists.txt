cmake_minimum_required(VERSION 3.0)

project(TooGoodEngine
	LANGUAGES CXX C)

# SDL2
if(WIN32)
	set(SDL2_PATH "${CMAKE_SOURCE_DIR}/external/SDL2-2.0.10")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
message(${SDL2_INCLUDE_DIR})

include_directories(${SDL2_INCLUDE_DIR})
#

include(CTest)
include_directories("include")

add_executable(TestSDL tests/TestSDL.cpp src/Vector3.cpp include/Vector3.hpp)
target_link_libraries(TestSDL ${SDL2_LIBRARY})

add_executable(Game src/Game.cpp src/Frame.cpp include/Frame.hpp src/Particle.cpp include/Particle.hpp src/Vector3.cpp include/Vector3.hpp)

add_executable(TestVector3 tests/TestVector3.cpp src/Vector3.cpp include/Vector3.hpp)
add_test(TestVector3 COMMAND "TestVector3")

# target_link_libraries(target ${SDL2_LIBRARY})