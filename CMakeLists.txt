cmake_minimum_required(VERSION 3.0)

project(TooGoodEngine
	LANGUAGES CXX C)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

# SDL2

if(WIN32)
	if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
		set(SDL2_PATH "${CMAKE_SOURCE_DIR}/external/SDL2-2.0.10/x86_64-w64-mingw32")
	else()
		set(SDL2_PATH "${CMAKE_SOURCE_DIR}/external/SDL2-2.0.10/i686-w64-mingw32")
	endif()
endif()

find_package(SDL2 REQUIRED)
message(${SDL2_INCLUDE_DIR})

include_directories(${SDL2_INCLUDE_DIR})
#

include(CTest)
include_directories("include")

add_executable(TestSDL src/Test.cpp)
target_link_libraries(TestSDL ${SDL2_LIBRARY})

add_executable(Particle src/Particle.cpp include/Particle.hpp src/Vector3.cpp include/Vector3.hpp)

add_executable(TestVector3 tests/TestVector3.cpp src/Vector3.cpp include/Vector3.hpp)
add_test(TestVector3 COMMAND "TestVector3")

# target_link_libraries(target ${SDL2_LIBRARY})