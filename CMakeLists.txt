cmake_minimum_required(VERSION 3.15)

if(DEFINED SKBUILD_PROJECT_NAME)
    set(IS_PYTHON_BUILD ON)
    project(${SKBUILD_PROJECT_NAME} VERSION ${SKBUILD_PROJECT_VERSION} LANGUAGES CXX)
    message(STATUS "Build Mode: C++ and Python bindings enabled)")
else()
    set(IS_PYTHON_BUILD OFF)
    project(geosample3d LANGUAGES CXX)
    message(STATUS "Build Mode: Standalone C++ (Python bindings disabled)")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# --- Dependencies ---

include(FetchContent)


#set(NANOFLANN_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
#set(NANOFLANN_BUILD_TESTS OFF CACHE BOOL "" FORCE)
#set(NANOFLANN_BUILD_BENCHMARKS OFF CACHE BOOL "" FORCE)

# nanoflann for KD-Tree implementation
#FetchContent_Declare(
#    nanoflann
#    GIT_REPOSITORY https://github.com/jlblancoc/nanoflann
#    GIT_TAG v1.8.0
#)
#FetchContent_MakeAvailable(nanoflann)

# OpenMP for parallel processing
find_package(OpenMP REQUIRED)


# --- Core C++ Library ---
set(CORE_SOURCES
    src/farthest_point_sampling.cpp
    src/poisson_disk_sampling.cpp
)

# Create a static library for the algorithms
add_library(geosample_core STATIC ${CORE_SOURCES})

# Include src/ directory for core library to find headers
target_include_directories(geosample_core PUBLIC src/)

# Link dependencies to core library
target_link_libraries(geosample_core PRIVATE 
    #nanoflann::nanoflann 
    OpenMP::OpenMP_CXX
)

if(IS_PYTHON_BUILD)

    # Pybind11 for Python bindings
    FetchContent_Declare(
        pybind11
        GIT_REPOSITORY https://github.com/pybind/pybind11
        GIT_TAG v3.0.1
    )
    FetchContent_MakeAvailable(pybind11)

    # Define python extension module
    pybind11_add_module(_geosample3d MODULE src/pybindings.cpp)

    # Link core library and pybind11 headers to the module
    target_link_libraries(_geosample3d PRIVATE geosample_core pybind11::headers)

    # Install to the package directory
    install(TARGETS _geosample3d DESTINATION geosample3d)

else()
    add_executable(main src/main.cpp)
    target_link_libraries(main PRIVATE geosample_core)
    message(STATUS "Standalone mode: Built 'main' executable")

endif()
