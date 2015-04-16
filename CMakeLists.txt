cmake_minimum_required(VERSION 2.8.4)
project(SdlPanelUi)

set (SdlPanelUi_VERSION_MAJOR 1)
set (SdlPanelUi_VERSION_MINOR 0)

set (SdlPanelUi_FB_WIDTH 640)
set (SdlPanelUi_FB_HEIGHT 480)


# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "src/config/cmake.h.in"
  "${PROJECT_BINARY_DIR}/SdlPanelUiConfig.h"
  )


# Use our modified FindSDL2 modules
# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${SdlPanelUi_SOURCE_DIR}/cmake")

# Set an output directory for our binaries
set(BIN_DIR ${PROJECT_BINARY_DIR}/bin)

# Source files
file(GLOB_RECURSE SOURCE_FILES "src/*.h" "src/*.cpp" "src/*.c" "src/*.rl")

# Bump up warning levels appropriately for clang, gcc & msvc
# Also set debug/optimization flags depending on the build type. IDE users choose this when
# selecting the build mode in their IDE
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++11 -ftemplate-backtrace-limit=0 -DSDL_MAIN_HANDLED")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -g")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -O2")

	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic -std=c99")


elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
	if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	endif()
endif()

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# Look up SDL2 and add the include directory to our include path
find_package(SDL REQUIRED)
include_directories(${SDL_INCLUDE_DIR})

find_package(SDL_image REQUIRED)
include_directories(${SDL_IMAGE_INCLUDE_DIRS})

find_package(SDL_ttf REQUIRED)
include_directories(${SDL_TTF_INCLUDE_DIRS})

find_package(Log4CPP REQUIRED)
include_directories(${LOG4CPP_INCLUDE_DIR})

find_package(Fruit REQUIRED)
include_directories(${FRUIT_INCLUDE_DIR})


# add the binary tree to the search path for include files
# so that we will find SdlPanelUiConfig.h
include_directories("${PROJECT_BINARY_DIR}")

# Project includes
include_directories(include)

add_executable(SdlPanelUi ${SOURCE_FILES})
target_link_libraries(SdlPanelUi ${SDL_LIBRARY})
target_link_libraries(SdlPanelUi ${SDL_IMAGE_LIBRARIES})
target_link_libraries(SdlPanelUi ${SDL_TTF_LIBRARIES})
target_link_libraries(SdlPanelUi ${LOG4CPP_LIBRARIES})
target_link_libraries(SdlPanelUi ${FRUIT_LIBRARIES})
install(DIRECTORY res DESTINATION ${PROJECT_BINARY_DIR})