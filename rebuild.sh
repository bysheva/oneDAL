#!/bin/bash
export WANT_GCC_VERSION=9.1.0
source ../daal-infra/bin/env/lnx32e.sh build gnu
export CC=$GCC_ROOT/bin/gcc
export CXX=$GCC_ROOT/bin/g++
export LIBRARY_PATH=${GCC_ROOT}/lib64:${LIBRARY_PATH}
make -j24 daal_c REQDBG=yes REQCPU=avx512 CORE.ALGORITHMS.CUSTOM=cholesky COMPILER=gnu
make -j24 onedal_c REQDBG=yes REQCPU=avx512 CORE.ALGORITHMS.CUSTOM=jaccard COMPILER=gnu

