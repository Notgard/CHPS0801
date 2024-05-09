cmake_minimum_required(VERSION 3.16)
project(KokkosStencilJacobi)
include(../../common.cmake)

FIND_PACKAGE( OpenCV REQUIRED )                              
INCLUDE_DIRECTORIES( ${OpenCV_INCLUDE_DIRS} )

add_executable(kokkos_jacobi cpu_parallel_jacobi.cpp)
target_link_libraries(kokkos_jacobi Kokkos::kokkos)
TARGET_LINK_LIBRARIES (kokkos_jacobi ${OpenCV_LIBS})  

