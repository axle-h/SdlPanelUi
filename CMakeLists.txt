cmake_minimum_required(VERSION 2.8.4)
project(SdlPanelUi)

set (SdlPanelUi_VERSION_MAJOR 1)
set (SdlPanelUi_VERSION_MINOR 0)

set (SdlPanelUi_FB_WIDTH 640)
set (SdlPanelUi_FB_HEIGHT 480)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# configure a header file to pass some of the CMake settings to the source code
configure_file (
  "cmake.h.in"
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.h"
  )

# add the binary tree to the search path for include files
# so that we will find SdlPanelUiConfig.h
include_directories("${PROJECT_BINARY_DIR}")

# Source files
file(GLOB_RECURSE SOURCE_FILES "src/*.h" "src/*.cpp")

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

find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)
find_package(SDL_ttf REQUIRED)
find_package(Log4CPP REQUIRED)
find_package(Fruit REQUIRED)
find_package(LibConfig++ REQUIRED)

# Project includes
include_directories(include
	${SDL_INCLUDE_DIR}
	${SDL_IMAGE_INCLUDE_DIRS}
	${SDL_TTF_INCLUDE_DIRS}
	${LOG4CPP_INCLUDE_DIR}
	${FRUIT_INCLUDE_DIR}
	${LIBCONFIG_INCLUDE_DIR})

# Build litehtml
file(GLOB_RECURSE LITEHTML_SRC_FILES include/litehtml/*.h include/litehtml/*.cpp include/litehtml/*.c include/litehtml/*.rl)
add_library(LiteHtml STATIC ${LITEHTML_SRC_FILES})

add_executable(SdlPanelUi ${SOURCE_FILES})
target_link_libraries(SdlPanelUi
	${SDL_LIBRARY}
	${SDL_IMAGE_LIBRARIES}
	${SDL_IMAGE_LIBRARIES}
	${SDL_TTF_LIBRARIES}
	${LOG4CPP_LIBRARIES}
	${FRUIT_LIBRARIES}
	${LIBCONFIG_LIBRARIES}
	LiteHtml)

install(TARGETS SdlPanelUi DESTINATION ${PROJECT_NAME}/bin)
install(FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.h" DESTINATION "${PROJECT_NAME}/include")
install(DIRECTORY resources DESTINATION ${PROJECT_NAME})