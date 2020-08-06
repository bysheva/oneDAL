#!/bin/bash
export WANT_GCC_VERSION=9.1.0
source ../daal-infra/bin/env/lnx32e.sh build
export CC=$GCC_ROOT/bin/gcc
export CXX=$GCC_ROOT/bin/g++
export LIBRARY_PATH=${GCC_ROOT}/lib64:${LIBRARY_PATH}

source __release_lnx_gnu/daal/latest/env/vars.sh
cd __release_lnx_gnu/daal/latest/examples/oneapi/cpp

# export DATAFILENAME=/nfs/inn/proj/numerics1/Users/orazvens/oneapi-onedal-orazve/graph_structure/examples/oneapi/cpp/source/jaccard/data.el
# ./_results/intel_intel64_parallel_a/jaccard_batch.exe $DATAFILENAME

declare -a DATASETS_TO_MEASURE=( 
    # "/nfs/inn/proj/numerics1/Users/orazvens/graph/better_make_graph/graph_algorithms_exploration/samples/wrong_numbers.csv" 
    # "/localdisk2/numerics/orazvens/data/USA-road-d.USA.el" 
    # "/localdisk2/numerics/orazvens/data/TheMarkerAnonymized0w.csv" 
    # "/localdisk2/numerics/orazvens/data/flixster00.mtx" 
    # "/localdisk2/numerics/orazvens/data/sas/amazon0302.txt" 
    # "/localdisk2/numerics/orazvens/data/sas/email-Enron.txt" 
    "/localdisk2/numerics/orazvens/data/sas/soc-Epinions1.txt" 
    # "/localdisk2/numerics/orazvens/data/sas/web-Google.txt" 
    # "/localdisk2/numerics/orazvens/data/indochina-2004.mtx" 
)

i=0

EXEC="./_results/intel_intel64_parallel_a/jaccard_batch.exe"

for DATASETPATH in "${DATASETS_TO_MEASURE[@]}"
do
    echo $DATASETPATH
    NAME=`basename $DATASETPATH`
    # gdb --args $EXEC $DATASETPATH
    $EXEC $DATASETPATH
    echo " "
    ((i=i+1))
done


