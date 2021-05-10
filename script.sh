#!/bin/bash


source setenv.sh

if [[ -z "${OTT_ROOT}" ]]; then
    echo "OTT_ROOT is undefined"
    exit 1
fi

env

echo "OTT_ROOT is defined"

if [ -e "build" ]; then
    echo "build dir is exist"
else
    mkdir -p build
fi

echo "building dependencies"

export DEPENDENCIES_ROOT=$OTT_ROOT/third_parties
pushd $DEPENDENCIES_ROOT
./build_depedencies.sh
popd
 
#export CMAKE_C_COMPILER=/usr/bin/gcc-10
#export CMAKE_CXX_COMPILER=/usr/bin/g++-10

pushd build
if [[ -z "${CMAKE_C_COMPILER}" ]]; then
    echo "Do use custom compiler"
    cmake  ..
else
    echo "use cusom compiler"
    cmake  -DCMAKE_C_COMPILER=$CMAKE_C_COMPILER  -DCMAKE_CXX_COMPILER=$CMAKE_CXX_COMPILER ..
fi

make -j4


popd



