cmake_minimum_required(VERSION 3.16)
project(KokkosStencilJacobi)
include(common.cmake)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__STRICT_ANSI__")

# Define source files including gaussianNoise.cpp
set(SOURCES parallel_jacobi.cpp gaussianNoise.cpp)

# Add executable with source files
add_executable(kokkos_jacobi ${SOURCES})

# Add compilation flags
target_compile_options(kokkos_jacobi PRIVATE
    -g                 # Generate debug information
    -std=c++11         # Use C++11
)

# Link Kokkos library
target_link_libraries(kokkos_jacobi Kokkos::kokkos)

# Link OpenCV libraries
target_link_libraries(kokkos_jacobi ${OpenCV_LIBS})
