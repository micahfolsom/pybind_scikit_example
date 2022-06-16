cmake_minimum_required(VERSION 3.15...3.22)
project(pybind_scikit_example VERSION "0.0.1")

# C++ options
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/build_options.cmake)

# pybind11/scikit_build
if(SKBUILD)
  # Scikit-Build does not add your site-packages to the search path
  # automatically, so we need to add it _or_ the pybind11 specific directory
  # here.
  execute_process(
    COMMAND "${PYTHON_EXECUTABLE}" -c
            "import pybind11; print(pybind11.get_cmake_dir())"
    OUTPUT_VARIABLE _tmp_dir
    OUTPUT_STRIP_TRAILING_WHITESPACE COMMAND_ECHO STDOUT)
  list(APPEND CMAKE_PREFIX_PATH "${_tmp_dir}")
endif()
# Now we can find pybind11
find_package(pybind11 CONFIG REQUIRED)

# HDF5 - install with "sudo apt install libhdf5-dev" on Ubuntu
#find_package(HDF5 REQUIRED)
#include_directories(${HDF5_INCLUDE_DIRS})

# Bingo source
set(BINGO_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/bingo_cpp)
include_directories(${BINGO_SOURCE_DIR})
file(GLOB BINGO_SOURCES ${BINGO_SOURCE_DIR}/*.cpp)
# Pingo source
set(PINGO_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/pingo_cpp)
include_directories(${PINGO_SOURCE_DIR})
file(GLOB PINGO_SOURCES ${PINGO_SOURCE_DIR}/*.cpp)

# Essentially a wrapper for target_link_libraries()
pybind11_add_module(bingo_cpp
  MODULE
  ${BINGO_SOURCES}
)
pybind11_add_module(pingo_cpp
  MODULE
  ${PINGO_SOURCES}
)
#target_link_libraries(pingo_cpp PRIVATE ${HDF5_LIBRARIES})

#target_compile_definitions(bingo_cpp
#  PRIVATE
#  VERSION_INFO=${PROJECT_VERSION}
#)

install(TARGETS bingo_cpp DESTINATION .)
install(TARGETS pingo_cpp DESTINATION .)
