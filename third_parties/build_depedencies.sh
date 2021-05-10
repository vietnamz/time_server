#!/bin/bash



set -e

echo "***********building dependenceis***************"


if [[ -n $DEPENDENCIES_ROOT ]]; then
    echo "$DEPENDENCIES_ROOT"
else
    export DEPENDENCIES_ROOT=`pwd`
fi

# build boost
$DEPENDENCIES_ROOT/boost/build.sh

