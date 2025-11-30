cmake_minimum_required(VERSION 3.15)
project(geosample3d LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Dependencies ---

include(FetchContent)

# Pybind11 for Python bindings
FetchContent_Declare(
    pybind11
    GIT_REPOSITORY https://github.com/pybind/pybind11
    GIT_TAG v3.0.1
)
FetchContent_MakeAvailable(pybind11)

# nanoflann for KD-Tree implementation
FetchContent_Declare(
    nanoflann
    GIT_REPOSITORY https://github.com/jlblancoc/nanoflann
    GIT_TAG v1.8.0
)
FetchContent_MakeAvailable(nanoflann)

# OpenMP for parallel processing
find_package(OpenMP REQUIRED)

# Define python extension module
pybind11_add_module(_geosample3d MODULE
    src/pybindings.cpp
    src/farthest_point_sampling.cpp
    src/poisson_disk_sampling.cpp
)

# --- Include Directory ---
target_include_directories(_geosample3d
    PRIVATE
        src/
)

# --- Link Libraries ---
target_link_libraries(_geosample3d
    PRIVATE
        nanoflann::nanoflann
        OpenMP::OpenMP_CXX
        pybind11::headers
)

install(TARGETS _geosample3d DESTINATION geosample3d)