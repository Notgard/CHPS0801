cmake_minimum_required(VERSION 3.16)
project(KokkosStencilJacobi)
include(../../common.cmake)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Define source files including gaussianNoise.cpp
set(SOURCES cpu_parallel_jacobi.cpp gaussianNoise.cpp)

# Add executable with source files
add_executable(kokkos_jacobi ${SOURCES})

# Link Kokkos library
target_link_libraries(kokkos_jacobi Kokkos::kokkos)

# Link OpenCV libraries
target_link_libraries(kokkos_jacobi ${OpenCV_LIBS})
