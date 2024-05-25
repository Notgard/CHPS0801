#!/bin/bash
if [[ $# -lt 1 || $# -gt 1 ]] ; then
	echo 'Wrong arguments provided, is new build required? (0 for no, 1 for yes)'
	exit 1
fi
if [[ $1 -eq 1 ]] ; then
    rm -rf gauss_seidel/build-cpu
    srun -n 1 -c 16 --reservation=CHPS cmake -B gauss_seidel/build-cpu -DKokkos_ENABLE_SERIAL=OFF -DKokkos_ENABLE_OPENMP=ON gauss_seidel/
fi
srun -n 1 -c 16 --reservation=CHPS cmake --build gauss_seidel/build-cpu --parallel
OMP_PROC_BIND=true srun -n 1 -c 16 --reservation=CHPS ./gauss_seidel/build-cpu/kokkos_gauss_seidel