cmake_minimum_required(VERSION 3.0)

project(TooGoodEngine
	LANGUAGES CXX C)
	
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

## SDL2
if(WIN32) # On Windows systems, search for libs in `external` directory
	set(SDL2_PATH "${CMAKE_SOURCE_DIR}/external/SDL2-2.0.10")
	set(SDL2_IMAGE_PATH "${CMAKE_SOURCE_DIR}/external/SDL2_image-2.0.5")
	set(GLEW_PATH "${CMAKE_SOURCE_DIR}/external/glew-2.1.0")
	set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${GLEW_PATH})
endif()

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIR})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIR})

set(OpenGL_GL_PREFERENCE LEGACY)
find_package(OPENGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

include(CTest)
include_directories("include")

###########################
#                         #
#         FORCES          #
#                         #
###########################

set(FORCES_GENERATORS_INCLUDES
	include/Forces/Generators.hpp
	include/Forces/IForceGenerator.hpp
	include/Forces/Generators/ForceGenerator.hpp
	include/Forces/Generators/Drag.hpp
	include/Forces/Generators/Spring.hpp
	include/Forces/Generators/BungeeSpring.hpp
	include/Forces/Generators/AnchoredSpring.hpp
	include/Forces/Generators/Buoyancy.hpp
	include/Forces/Generators/StiffSpring.hpp
	include/Forces/Generators/Gravity.hpp
)

set(FORCES_GENERATORS_SOURCES
	src/Forces/Generators/Gravity.cpp
	src/Forces/Generators/Drag.cpp
	src/Forces/Generators/Spring.cpp
	src/Forces/Generators/BungeeSpring.cpp
	src/Forces/Generators/AnchoredSpring.cpp
	src/Forces/Generators/Buoyancy.cpp
	src/Forces/Generators/StiffSpring.cpp
)

set(FORCES_INCLUDES
	include/Forces/Registery.hpp
	${FORCE_GENERATORS_INCLUDES}
)

set(FORCES_SOURCES
	src/Forces/Registery.cpp
	${FORCES_GENERATORS_SOURCES}
)

###########################
#                         #
#        CONTACTS         #
#                         #
###########################

set(CONTACTS_GENERATORS_INCLUDES
	include/Contacts/IContactGenerator.hpp
	include/Contacts/Generators/Link.hpp
	include/Contacts/Generators/Cable.hpp
)

set(CONTACTS_GENERATORS_SOURCES
	src/Contacts/Generators/Link.cpp
	src/Contacts/Generators/Cable.cpp
)

set(CONTACTS_INCLUDES
	include/Contacts/Contact.hpp
	#include/Contacts/Resolver.hpp
)

set(CONTACTS_SOURCES
	src/Contacts/Contact.cpp
	#src/Contacts/Resolver.cpp
)

# TooGoodEngine Library
add_library(TooGoodEngineLib
	#COMMON
	src/Vector3.cpp			include/Vector3.hpp
	src/Quaternion.cpp		include/Quaternion.hpp
	src/Matrix3.cpp			include/Matrix3.hpp
	src/Transform.cpp		include/Transform.hpp
	src/Particle.cpp		include/Particle.hpp
	src/RigidBody.cpp		include/RigidBody.hpp
	include/Primitive.hpp
	src/BoxPrimitive.cpp	include/BoxPrimitive.hpp
	src/PlanPrimitive.cpp	include/PlanPrimitive.hpp
	#FORCES
	${FORCES_SOURCES}		${FORCES_INCLUDES}
	#CONTACTS
	${CONTACTS_SOURCES}		${CONTACTS_INCLUDES}
	include/Contacts/BoundingSphere.hpp
	src/CollisionData.cpp	include/CollisionData.hpp
	src/BSPTree.cpp			include/BSPTree.hpp
	#SDL
	include/CommonSDL.hpp
	src/GameSDL.cpp			include/GameSDL.hpp
	src/Frame.cpp			include/Frame.hpp
	src/Sprite.cpp			include/Sprite.hpp
	src/BoxRigidBody.cpp	include/BoxRigidBody.hpp
	src/Cube.cpp			include/Cube.hpp
	#OPENGL
	src/OpenGLScene.cpp		include/OpenGLScene.hpp
	src/Shader.cpp			include/Shader.hpp 
	src/Element.cpp			include/Element.hpp
	src/Graph3DModel.cpp	include/Graph3DModel.hpp
	src/Box3DModel.cpp		include/Box3DModel.hpp)

target_link_libraries(TooGoodEngineLib PUBLIC ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})

if(WIN32) # On Windows systems, copy .dll to build directory
	if(CMAKE_SIZEOF_VOID_P EQUAL 8)
		SET(ARCH_PATH "x64")
	else()
		SET(ARCH_PATH "x86")
	endif()
	add_custom_command(TARGET TooGoodEngineLib POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SDL2_PATH}/lib/${ARCH_PATH}/SDL2.dll $<TARGET_FILE_DIR:TooGoodEngineLib>)
	add_custom_command(TARGET TooGoodEngineLib POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SDL2_IMAGE_PATH}/lib/${ARCH_PATH}/libjpeg-9.dll $<TARGET_FILE_DIR:TooGoodEngineLib>)
	add_custom_command(TARGET TooGoodEngineLib POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SDL2_IMAGE_PATH}/lib/${ARCH_PATH}/libpng16-16.dll $<TARGET_FILE_DIR:TooGoodEngineLib>)
	add_custom_command(TARGET TooGoodEngineLib POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SDL2_IMAGE_PATH}/lib/${ARCH_PATH}/libtiff-5.dll $<TARGET_FILE_DIR:TooGoodEngineLib>)
	add_custom_command(TARGET TooGoodEngineLib POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SDL2_IMAGE_PATH}/lib/${ARCH_PATH}/libwebp-7.dll $<TARGET_FILE_DIR:TooGoodEngineLib>)
	add_custom_command(TARGET TooGoodEngineLib POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SDL2_IMAGE_PATH}/lib/${ARCH_PATH}/zlib1.dll $<TARGET_FILE_DIR:TooGoodEngineLib>)
	add_custom_command(TARGET TooGoodEngineLib POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SDL2_IMAGE_PATH}/lib/${ARCH_PATH}/SDL2_image.dll $<TARGET_FILE_DIR:TooGoodEngineLib>)
	add_custom_command(TARGET TooGoodEngineLib POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${GLEW_PATH}/bin/Release/${ARCH_PATH}/glew32.dll $<TARGET_FILE_DIR:TooGoodEngineLib>)
endif()

add_custom_command(TARGET TooGoodEngineLib POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/sprites $<TARGET_FILE_DIR:TooGoodEngineLib>/sprites)
add_custom_command(TARGET TooGoodEngineLib POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/Shaders $<TARGET_FILE_DIR:TooGoodEngineLib>/Shaders)

# Game2 demo executable
add_executable(Game2 src/Game2.cpp)
target_link_libraries(Game2 TooGoodEngineLib)

# TestVector3
add_executable(TestVector3 tests/TestVector3.cpp)
target_link_libraries(TestVector3 TooGoodEngineLib)
add_test(Test_Vector3 TestVector3)

# TestQuaternion
add_executable(TestQuaternion tests/TestQuaternion.cpp)
target_link_libraries(TestQuaternion TooGoodEngineLib)
add_test(Test_Quaternion TestQuaternion)

# TestMatrix3
add_executable(TestMatrix3 tests/TestMatrix3.cpp)
target_link_libraries(TestMatrix3 TooGoodEngineLib)
add_test(Test_Quaternion TestMatrix3)

# TestTransform
add_executable(TestTransform tests/TestTransform.cpp)
target_link_libraries(TestTransform TooGoodEngineLib)
add_test(Test_Quaternion TestTransform)

# TestRigidBody
add_executable(TestRigidBody tests/TestRigidBody.cpp)
target_link_libraries(TestRigidBody TooGoodEngineLib)
add_test(Test_Quaternion TestRigidBody)

# Test 3D
add_executable(Test3D tests/Test3D.cpp)
target_link_libraries(Test3D TooGoodEngineLib)

# Test 3D
add_executable(TestBSPTree tests/TestBSPTree.cpp)
target_link_libraries(TestBSPTree TooGoodEngineLib)