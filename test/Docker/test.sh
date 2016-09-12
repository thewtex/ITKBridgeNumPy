#!/bin/bash

# This is a script to build the modules and run the test suite in the base
# Docker container.

set -o
set -x

cd /usr/src/ITKBridgeNumPy
branch=$(git rev-parse --abbrev-ref HEAD)
date=$(date +%F_%H_%M_%S)
sha=$(git rev-parse --short HEAD)

cd /usr/src/ITKBridgeNumPy-build
cmake \
  -G Ninja \
  -DITK_DIR:PATH=/usr/src/ITK-build \
  -DCMAKE_BUILD_TYPE:STRING=Release \
  -DBUILDNAME:STRING=External-BridgeNumPy-${branch}-${date}-${sha} \
    /usr/src/ITKBridgeNumPy
ctest -VV -D Experimental
