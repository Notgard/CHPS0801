set(CMAKE_C_COMPILER "/apps/2021/llvm/11.0.0/bin/clang")
set(CMAKE_C_COMPILER_ARG1 "")
set(CMAKE_C_COMPILER_ID "Clang")
set(CMAKE_C_COMPILER_VERSION "11.0.0")
set(CMAKE_C_COMPILER_VERSION_INTERNAL "")
set(CMAKE_C_COMPILER_WRAPPER "")
set(CMAKE_C_STANDARD_COMPUTED_DEFAULT "11")
set(CMAKE_C_COMPILE_FEATURES "c_std_90;c_function_prototypes;c_std_99;c_restrict;c_variadic_macros;c_std_11;c_static_assert")
set(CMAKE_C90_COMPILE_FEATURES "c_std_90;c_function_prototypes")
set(CMAKE_C99_COMPILE_FEATURES "c_std_99;c_restrict;c_variadic_macros")
set(CMAKE_C11_COMPILE_FEATURES "c_std_11;c_static_assert")

set(CMAKE_C_PLATFORM_ID "Linux")
set(CMAKE_C_SIMULATE_ID "")
set(CMAKE_C_COMPILER_FRONTEND_VARIANT "GNU")
set(CMAKE_C_SIMULATE_VERSION "")




set(CMAKE_AR "/usr/bin/ar")
set(CMAKE_C_COMPILER_AR "/apps/2021/llvm/11.0.0/bin/llvm-ar")
set(CMAKE_RANLIB "/usr/bin/ranlib")
set(CMAKE_C_COMPILER_RANLIB "/apps/2021/llvm/11.0.0/bin/llvm-ranlib")
set(CMAKE_LINKER "/usr/bin/ld")
set(CMAKE_MT "")
set(CMAKE_COMPILER_IS_GNUCC )
set(CMAKE_C_COMPILER_LOADED 1)
set(CMAKE_C_COMPILER_WORKS TRUE)
set(CMAKE_C_ABI_COMPILED TRUE)
set(CMAKE_COMPILER_IS_MINGW )
set(CMAKE_COMPILER_IS_CYGWIN )
if(CMAKE_COMPILER_IS_CYGWIN)
  set(CYGWIN 1)
  set(UNIX 1)
endif()

set(CMAKE_C_COMPILER_ENV_VAR "CC")

if(CMAKE_COMPILER_IS_MINGW)
  set(MINGW 1)
endif()
set(CMAKE_C_COMPILER_ID_RUN 1)
set(CMAKE_C_SOURCE_FILE_EXTENSIONS c;m)
set(CMAKE_C_IGNORE_EXTENSIONS h;H;o;O;obj;OBJ;def;DEF;rc;RC)
set(CMAKE_C_LINKER_PREFERENCE 10)

# Save compiler ABI information.
set(CMAKE_C_SIZEOF_DATA_PTR "8")
set(CMAKE_C_COMPILER_ABI "ELF")
set(CMAKE_C_LIBRARY_ARCHITECTURE "")

if(CMAKE_C_SIZEOF_DATA_PTR)
  set(CMAKE_SIZEOF_VOID_P "${CMAKE_C_SIZEOF_DATA_PTR}")
endif()

if(CMAKE_C_COMPILER_ABI)
  set(CMAKE_INTERNAL_PLATFORM_ABI "${CMAKE_C_COMPILER_ABI}")
endif()

if(CMAKE_C_LIBRARY_ARCHITECTURE)
  set(CMAKE_LIBRARY_ARCHITECTURE "")
endif()

set(CMAKE_C_CL_SHOWINCLUDES_PREFIX "")
if(CMAKE_C_CL_SHOWINCLUDES_PREFIX)
  set(CMAKE_CL_SHOWINCLUDES_PREFIX "${CMAKE_C_CL_SHOWINCLUDES_PREFIX}")
endif()





set(CMAKE_C_IMPLICIT_INCLUDE_DIRECTORIES "/apps/2021/opencv/4.5.2-contrib/include/opencv4;/apps/2021/llvm/11.0.0/include;/apps/spack/0.16.0/opt/spack/linux-rhel7-skylake_avx512/gcc-10.2.0/libffi-3.3-cekv3mhygvn5fq2gr22ljv662iunrcsh/include;/apps/spack/0.16.0/opt/spack/linux-rhel7-skylake_avx512/gcc-10.2.0/libelf-0.8.13-m5ndvdx7mc7al3xfq2venrdfo2laoy3g/include;/apps/spack/0.16.0/opt/spack/linux-rhel7-haswell/gcc-4.8.5/isl-0.18-zwfd4x6n3v3vads3ncukk5mtgt6xv2qj/include;/apps/spack/0.16.0/opt/spack/linux-rhel7-haswell/gcc-4.8.5/mpc-1.1.0-ijex5qs7pt44n7whqlgwqj4jwc3czkac/include;/apps/spack/0.16.0/opt/spack/linux-rhel7-haswell/gcc-4.8.5/mpfr-4.0.2-yfoprebczoqpokivqgmnjn5os4r7mxw6/include;/apps/spack/0.16.0/opt/spack/linux-rhel7-haswell/gcc-4.8.5/gmp-6.1.2-raqmdaosldybjrn6y2xnnnyy2f63hg6b/include;/apps/2021/cuda/10.1/include;/apps/spack/0.16.0/opt/spack/linux-rhel7-skylake_avx512/gcc-10.2.0/openssl-1.1.1h-iwybd6raqg2jisesulhn4eq4u6pua4r5/include;/apps/spack/0.16.0/opt/spack/linux-rhel7-skylake_avx512/gcc-10.2.0/zlib-1.2.11-cd5sn7qr4dpsl52yco7o4un6svatshid/include;/apps/spack/0.16.0/opt/spack/linux-rhel7-skylake_avx512/gcc-10.2.0/ncurses-6.2-hjedt2uy7o2piyycr3ttni2puoezbfu6/include;/usr/local/include;/apps/2021/llvm/11.0.0/lib/clang/11.0.0/include;/usr/include")
set(CMAKE_C_IMPLICIT_LINK_LIBRARIES "gcc;gcc_s;c;gcc;gcc_s")
set(CMAKE_C_IMPLICIT_LINK_DIRECTORIES "/apps/spack/0.16.0/opt/spack/linux-rhel7-skylake_avx512/gcc-10.2.0/gcc-8.1.0-gptuaqlbqaldiydae2dtm7jojw6vy6hi/lib/gcc/x86_64-pc-linux-gnu/8.1.0;/apps/spack/0.16.0/opt/spack/linux-rhel7-skylake_avx512/gcc-10.2.0/gcc-8.1.0-gptuaqlbqaldiydae2dtm7jojw6vy6hi/lib64;/lib64;/usr/lib64;/apps/spack/0.16.0/opt/spack/linux-rhel7-skylake_avx512/gcc-10.2.0/gcc-8.1.0-gptuaqlbqaldiydae2dtm7jojw6vy6hi/lib;/apps/2021/llvm/11.0.0/lib;/lib;/usr/lib;/apps/2021/llvm/11.0.0/libexec;/apps/spack/0.16.0/opt/spack/linux-rhel7-skylake_avx512/gcc-10.2.0/libffi-3.3-cekv3mhygvn5fq2gr22ljv662iunrcsh/lib64;/apps/spack/0.16.0/opt/spack/linux-rhel7-skylake_avx512/gcc-10.2.0/libffi-3.3-cekv3mhygvn5fq2gr22ljv662iunrcsh/lib;/apps/spack/0.16.0/opt/spack/linux-rhel7-skylake_avx512/gcc-10.2.0/libelf-0.8.13-m5ndvdx7mc7al3xfq2venrdfo2laoy3g/lib;/apps/spack/0.16.0/opt/spack/linux-rhel7-haswell/gcc-4.8.5/isl-0.18-zwfd4x6n3v3vads3ncukk5mtgt6xv2qj/lib;/apps/spack/0.16.0/opt/spack/linux-rhel7-haswell/gcc-4.8.5/mpc-1.1.0-ijex5qs7pt44n7whqlgwqj4jwc3czkac/lib;/apps/spack/0.16.0/opt/spack/linux-rhel7-haswell/gcc-4.8.5/mpfr-4.0.2-yfoprebczoqpokivqgmnjn5os4r7mxw6/lib;/apps/spack/0.16.0/opt/spack/linux-rhel7-haswell/gcc-4.8.5/gmp-6.1.2-raqmdaosldybjrn6y2xnnnyy2f63hg6b/lib;/apps/spack/0.16.0/opt/spack/linux-rhel7-skylake_avx512/gcc-10.2.0/openssl-1.1.1h-iwybd6raqg2jisesulhn4eq4u6pua4r5/lib;/apps/spack/0.16.0/opt/spack/linux-rhel7-skylake_avx512/gcc-10.2.0/zlib-1.2.11-cd5sn7qr4dpsl52yco7o4un6svatshid/lib;/apps/spack/0.16.0/opt/spack/linux-rhel7-skylake_avx512/gcc-10.2.0/ncurses-6.2-hjedt2uy7o2piyycr3ttni2puoezbfu6/lib;/apps/2021/opencv/4.5.2-contrib/lib64")
set(CMAKE_C_IMPLICIT_LINK_FRAMEWORK_DIRECTORIES "")
