#!/bin/bash
export WANT_GCC_VERSION=9.1.0
source ../daal-infra/bin/env/lnx32e.sh build
export CC=$GCC_ROOT/bin/gcc
export CXX=$GCC_ROOT/bin/g++
export LIBRARY_PATH=${GCC_ROOT}/lib64:${LIBRARY_PATH}

source __release_lnx_gnu/daal/latest/env/vars.sh
rm -rf __release_lnx_gnu/daal/latest/examples/oneapi/cpp/_results/
cd __release_lnx_gnu/daal/latest/examples/oneapi/cpp
make libintel64 example=jaccard_batch

