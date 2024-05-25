#!/bin/bash
if [[ $# -lt 1 || $# -gt 1 ]] ; then
	echo 'Wrong arguments provided, is new build required? (0 for no, 1 for yes)'
	exit 1
fi
if [[ $1 -eq 1 ]] ; then
    rm -rf jacobi/build-cpu
    srun -n 1 -c 16 --reservation=CHPS cmake -B jacobi/build-cpu -DKokkos_ENABLE_SERIAL=OFF -DKokkos_ENABLE_OPENMP=ON jacobi/
fi
srun -n 1 -c 16 --reservation=CHPS cmake --build jacobi/build-cpu --parallel
OMP_PROC_BIND=true srun -n 1 -c 16 --reservation=CHPS ./jacobi/build-cpu/kokkos_jacobi