# Copyright (C) 2019 by Ilya Glushchenko
# This code is licensed under the MIT license (MIT)
# (http://opensource.org/licenses/MIT)

cmake_minimum_required (VERSION 3.1)

project(Ray)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

set(RAY_ROOT
    ${PROJECT_SOURCE_DIR}
)

set(RAY_INCLUDE_DIR
    ${RAY_ROOT}/include
)

include_directories (
    ${RAY_INCLUDE_DIR}
)

#STB
include(StbConfig)
include_directories(${STB_INCLUDE_DIR})

set(DEMO_HEADERS
	include/Definitions.hpp
	include/Collision.hpp
	include/Math.hpp
)
set(DEMO_SOURCES 
	source/Main.cpp
)

add_executable (${PROJECT_NAME}
    ${DEMO_SOURCES}
    ${DEMO_HEADERS}
)

target_compile_features(${PROJECT_NAME}
    PRIVATE cxx_std_17
)
