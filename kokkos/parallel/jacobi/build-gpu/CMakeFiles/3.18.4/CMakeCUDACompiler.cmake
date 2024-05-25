set(CMAKE_CUDA_COMPILER "/apps/2021/cuda/10.1/bin/nvcc")
set(CMAKE_CUDA_HOST_COMPILER "")
set(CMAKE_CUDA_HOST_LINK_LAUNCHER "/apps/2021/gcc/8.1.0/bin/g++")
set(CMAKE_CUDA_COMPILER_ID "NVIDIA")
set(CMAKE_CUDA_COMPILER_VERSION "10.1.105")
set(CMAKE_CUDA_STANDARD_COMPUTED_DEFAULT "14")
set(CMAKE_CUDA_COMPILE_FEATURES "cuda_std_03;cuda_std_11;cuda_std_14")
set(CMAKE_CUDA03_COMPILE_FEATURES "cuda_std_03")
set(CMAKE_CUDA11_COMPILE_FEATURES "cuda_std_11")
set(CMAKE_CUDA14_COMPILE_FEATURES "cuda_std_14")
set(CMAKE_CUDA17_COMPILE_FEATURES "")
set(CMAKE_CUDA20_COMPILE_FEATURES "")

set(CMAKE_CUDA_PLATFORM_ID "Linux")
set(CMAKE_CUDA_SIMULATE_ID "GNU")
set(CMAKE_CUDA_COMPILER_FRONTEND_VARIANT "")
set(CMAKE_CUDA_SIMULATE_VERSION "8.1")



set(CMAKE_CUDA_COMPILER_ENV_VAR "CUDACXX")
set(CMAKE_CUDA_HOST_COMPILER_ENV_VAR "CUDAHOSTCXX")

set(CMAKE_CUDA_COMPILER_LOADED 1)
set(CMAKE_CUDA_COMPILER_ID_RUN 1)
set(CMAKE_CUDA_SOURCE_FILE_EXTENSIONS cu)
set(CMAKE_CUDA_LINKER_PREFERENCE 15)
set(CMAKE_CUDA_LINKER_PREFERENCE_PROPAGATES 1)

set(CMAKE_CUDA_SIZEOF_DATA_PTR "8")
set(CMAKE_CUDA_COMPILER_ABI "ELF")
set(CMAKE_CUDA_LIBRARY_ARCHITECTURE "")

if(CMAKE_CUDA_SIZEOF_DATA_PTR)
  set(CMAKE_SIZEOF_VOID_P "${CMAKE_CUDA_SIZEOF_DATA_PTR}")
endif()

if(CMAKE_CUDA_COMPILER_ABI)
  set(CMAKE_INTERNAL_PLATFORM_ABI "${CMAKE_CUDA_COMPILER_ABI}")
endif()

if(CMAKE_CUDA_LIBRARY_ARCHITECTURE)
  set(CMAKE_LIBRARY_ARCHITECTURE "")
endif()

set(CMAKE_CUDA_COMPILER_TOOLKIT_ROOT "/apps/2021/cuda/10.1")
set(CMAKE_CUDA_COMPILER_LIBRARY_ROOT "/apps/2021/cuda/10.1")

set(CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES "/apps/2021/cuda/10.1/targets/x86_64-linux/include")

set(CMAKE_CUDA_HOST_IMPLICIT_LINK_LIBRARIES "")
set(CMAKE_CUDA_HOST_IMPLICIT_LINK_DIRECTORIES "/apps/2021/cuda/10.1/targets/x86_64-linux/lib/stubs;/apps/2021/cuda/10.1/targets/x86_64-linux/lib")
set(CMAKE_CUDA_HOST_IMPLICIT_LINK_FRAMEWORK_DIRECTORIES "")

set(CMAKE_CUDA_IMPLICIT_INCLUDE_DIRECTORIES "/apps/2021/opencv/4.5.2-contrib/include/opencv4;/apps/2021/llvm/11.0.0/include;/apps/spack/0.16.0/opt/spack/linux-rhel7-skylake_avx512/gcc-10.2.0/libffi-3.3-cekv3mhygvn5fq2gr22ljv662iunrcsh/include;/apps/spack/0.16.0/opt/spack/linux-rhel7-skylake_avx512/gcc-10.2.0/libelf-0.8.13-m5ndvdx7mc7al3xfq2venrdfo2laoy3g/include;/apps/spack/0.16.0/opt/spack/linux-rhel7-haswell/gcc-4.8.5/isl-0.18-zwfd4x6n3v3vads3ncukk5mtgt6xv2qj/include;/apps/spack/0.16.0/opt/spack/linux-rhel7-haswell/gcc-4.8.5/mpc-1.1.0-ijex5qs7pt44n7whqlgwqj4jwc3czkac/include;/apps/spack/0.16.0/opt/spack/linux-rhel7-haswell/gcc-4.8.5/mpfr-4.0.2-yfoprebczoqpokivqgmnjn5os4r7mxw6/include;/apps/spack/0.16.0/opt/spack/linux-rhel7-haswell/gcc-4.8.5/gmp-6.1.2-raqmdaosldybjrn6y2xnnnyy2f63hg6b/include;/apps/2021/cuda/10.1/include;/apps/spack/0.16.0/opt/spack/linux-rhel7-skylake_avx512/gcc-10.2.0/openssl-1.1.1h-iwybd6raqg2jisesulhn4eq4u6pua4r5/include;/apps/spack/0.16.0/opt/spack/linux-rhel7-skylake_avx512/gcc-10.2.0/zlib-1.2.11-cd5sn7qr4dpsl52yco7o4un6svatshid/include;/apps/spack/0.16.0/opt/spack/linux-rhel7-skylake_avx512/gcc-10.2.0/ncurses-6.2-hjedt2uy7o2piyycr3ttni2puoezbfu6/include;/apps/2021/gcc/8.1.0/include/c++/8.1.0;/apps/2021/gcc/8.1.0/include/c++/8.1.0/x86_64-pc-linux-gnu;/apps/2021/gcc/8.1.0/include/c++/8.1.0/backward;/apps/2021/gcc/8.1.0/lib/gcc/x86_64-pc-linux-gnu/8.1.0/include;/usr/local/include;/apps/2021/gcc/8.1.0/include;/apps/2021/gcc/8.1.0/lib/gcc/x86_64-pc-linux-gnu/8.1.0/include-fixed;/usr/include")
set(CMAKE_CUDA_IMPLICIT_LINK_LIBRARIES "stdc++;m;gcc_s;gcc;c;gcc_s;gcc")
set(CMAKE_CUDA_IMPLICIT_LINK_DIRECTORIES "/apps/2021/cuda/10.1/targets/x86_64-linux/lib/stubs;/apps/2021/cuda/10.1/targets/x86_64-linux/lib;/apps/spack/0.16.0/opt/spack/linux-rhel7-skylake_avx512/gcc-10.2.0/libffi-3.3-cekv3mhygvn5fq2gr22ljv662iunrcsh/lib64;/apps/2021/opencv/4.5.2-contrib/lib64;/apps/2021/gcc/8.1.0/lib/gcc/x86_64-pc-linux-gnu/8.1.0;/apps/2021/gcc/8.1.0/lib64;/lib64;/usr/lib64;/apps/2021/llvm/11.0.0/lib;/apps/2021/llvm/11.0.0/libexec;/apps/spack/0.16.0/opt/spack/linux-rhel7-skylake_avx512/gcc-10.2.0/libffi-3.3-cekv3mhygvn5fq2gr22ljv662iunrcsh/lib;/apps/spack/0.16.0/opt/spack/linux-rhel7-skylake_avx512/gcc-10.2.0/libelf-0.8.13-m5ndvdx7mc7al3xfq2venrdfo2laoy3g/lib;/apps/spack/0.16.0/opt/spack/linux-rhel7-haswell/gcc-4.8.5/isl-0.18-zwfd4x6n3v3vads3ncukk5mtgt6xv2qj/lib;/apps/spack/0.16.0/opt/spack/linux-rhel7-haswell/gcc-4.8.5/mpc-1.1.0-ijex5qs7pt44n7whqlgwqj4jwc3czkac/lib;/apps/spack/0.16.0/opt/spack/linux-rhel7-haswell/gcc-4.8.5/mpfr-4.0.2-yfoprebczoqpokivqgmnjn5os4r7mxw6/lib;/apps/spack/0.16.0/opt/spack/linux-rhel7-haswell/gcc-4.8.5/gmp-6.1.2-raqmdaosldybjrn6y2xnnnyy2f63hg6b/lib;/apps/spack/0.16.0/opt/spack/linux-rhel7-skylake_avx512/gcc-10.2.0/openssl-1.1.1h-iwybd6raqg2jisesulhn4eq4u6pua4r5/lib;/apps/spack/0.16.0/opt/spack/linux-rhel7-skylake_avx512/gcc-10.2.0/zlib-1.2.11-cd5sn7qr4dpsl52yco7o4un6svatshid/lib;/apps/spack/0.16.0/opt/spack/linux-rhel7-skylake_avx512/gcc-10.2.0/ncurses-6.2-hjedt2uy7o2piyycr3ttni2puoezbfu6/lib;/apps/2021/gcc/8.1.0/lib")
set(CMAKE_CUDA_IMPLICIT_LINK_FRAMEWORK_DIRECTORIES "")

set(CMAKE_CUDA_RUNTIME_LIBRARY_DEFAULT "STATIC")

set(CMAKE_LINKER "/usr/bin/ld")
set(CMAKE_AR "/usr/bin/ar")
set(CMAKE_MT "")
