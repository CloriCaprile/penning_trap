cmake_minimum_required(VERSION 3.12)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENTIONS OFF)

# Define a "project", providing a description and a programming language
project(penningtrap
	VERSION 1.0
	DESCRIPTION "Project 3 of Computational Physics course"
	LANGUAGES CXX
)
enable_testing()

# --- LIBRARY ---
add_library(trace 
	src/header.cpp
	src/particle.cpp
	src/penning.cpp)

#find_package(OpenMP REQUIRED)
#target_link_libraries(trace PUBLIC OpenMP::OpenMP_CXX)

find_package(Armadillo REQUIRED)
target_link_libraries(trace PUBLIC ${ARMADILLO_LIBRARIES})
include_directories(${ARMADILLO_INCLUDE_DIRS})

# This is needed if we keep .h files in the "include" directory
target_include_directories (trace PUBLIC 
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
	${ARMADILLO_LIBRARIES}
	)

# --- EXECUTABLES ---
add_executable(main
	main.cpp)
target_link_libraries(main PUBLIC trace)
#target_compile_features(p2 PUBLIC cxx_std_11)

# --- TESTS ---
#add_executable(particle-test
#    test/particle-test.cpp)
#target_link_libraries(particle-test PUBLIC trace)
#add_test(NAME particle-test COMMAND particle-test)

#add_executable(penning-test
#    test/penning-test.cpp)
#target_link_libraries(pennning-test PUBLIC trace)
#add_test(NAME penning-test COMMAND penning-test)