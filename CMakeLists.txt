CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(CppUtils)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	MESSAGE(STATUS "64-bit compiler detected!")
else(CMAKE_SIZEOF_VOID_P EQUAL 8)
	MESSAGE(STATUS "32-bit compiler detected!")
endif(CMAKE_SIZEOF_VOID_P EQUAL 8)

if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
   message(WARNING "In-source building is discouraged!")
endif("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")

ADD_EXECUTABLE(CppUtils
	src/iterator/generate.hpp
	src/logging/log.hpp
	src/math/vec.hpp
	src/random/shuffle.hpp
	src/random/rng.hpp
	src/time/timer.hpp
	src/main.cpp
)