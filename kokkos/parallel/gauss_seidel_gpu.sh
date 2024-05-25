#!/bin/bash
if [[ $# -lt 1 || $# -gt 1 ]] ; then
	echo 'Wrong arguments provided, is new build required? (0 for no, 1 for yes)'
	exit 1
fi
if [[ $1 -eq 1 ]] ; then
    rm -rf gauss_seidel/build-gpu
    CUDA_VISIBLE_DEVICES=0 srun --gres=gpu:1 --reservation=CHPS cmake -B gauss_seidel/build-gpu -DKokkos_ENABLE_CUDA=ON -DKokkos_ARCH_PASCAL60=ON gauss_seidel/
fi
CUDA_VISIBLE_DEVICES=0 srun --gres=gpu:1 --reservation=CHPS cmake --build gauss_seidel/build-gpu --parallel
CUDA_VISIBLE_DEVICES=0 srun --gres=gpu:1 --reservation=CHPS ./gauss_seidel/build-gpu/kokkos_gauss_seidel