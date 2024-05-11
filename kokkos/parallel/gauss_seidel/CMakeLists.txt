cmake_minimum_required(VERSION 3.16)
project(KokkosStencilGaussSeidel)
include(../../common.cmake)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Define source files including gaussianNoise.cpp
set(SOURCES parallel_gauss_seidel.cpp gaussianNoise.cpp)

# Add executable with source files
add_executable(kokkos_gauss_seidel ${SOURCES})

# Add compilation flags
target_compile_options(kokkos_gauss_seidel PRIVATE
    -g                 # Generate debug information
)

# Link Kokkos library
target_link_libraries(kokkos_gauss_seidel Kokkos::kokkos)

# Link OpenCV libraries
target_link_libraries(kokkos_gauss_seidel ${OpenCV_LIBS})
