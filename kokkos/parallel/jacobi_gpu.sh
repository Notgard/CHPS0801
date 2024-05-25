#!/bin/bash
if [[ $# -lt 1 || $# -gt 1 ]] ; then
	echo 'Wrong arguments provided, is new build required? (0 for no, 1 for yes)'
	exit 1
fi
if [[ $1 -eq 1 ]] ; then
    rm -rf jacobi/build-gpu
    CUDA_VISIBLE_DEVICES=0 srun --gres=gpu:1 --reservation=CHPS cmake -B jacobi/build-gpu -DKokkos_ENABLE_CUDA=ON jacobi/
fi
CUDA_VISIBLE_DEVICES=0 srun --gres=gpu:1 --reservation=CHPS cmake --build jacobi/build-gpu --parallel
CUDA_VISIBLE_DEVICES=0 srun --gres=gpu:1 --reservation=CHPS ./jacobi/build-gpu/kokkos_jacobi