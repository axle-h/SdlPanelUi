cmake_minimum_required(VERSION 2.8.4)
project(SdlPanelUi)

set (SdlPanelUi_VERSION_MAJOR 1)
set (SdlPanelUi_VERSION_MINOR 0)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/src/SdlPanelUiConfig.h.in"
  "${PROJECT_BINARY_DIR}/SdlPanelUiConfig.h"
  )


# Use our modified FindSDL2 modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${SdlPanelUi_SOURCE_DIR}/cmake")

# Set an output directory for our binaries
set(BIN_DIR ${PROJECT_BINARY_DIR}/bin)

# Source files
set(SOURCE_FILES src/main.cpp)

# Bump up warning levels appropriately for clang, gcc & msvc
# Also set debug/optimization flags depending on the build type. IDE users choose this when
# selecting the build mode in their IDE
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++11")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -g")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -O2")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
	if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	endif()
endif()

# Look up SDL2 and add the include directory to our include path
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

# Project includes
include_directories(include)

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")

add_executable(SdlPanelUi ${SOURCE_FILES})
target_link_libraries(SdlPanelUi ${SDL2_LIBRARY})
install(DIRECTORY res DESTINATION res)