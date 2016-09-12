#!/bin/sh

script_dir="`cd $(dirname $0); pwd`"

docker run \
  --rm \
  -v $script_dir/../..:/usr/src/ITKBridgeNumPy \
    insighttoolkit/bridgenumpy-test \
      /usr/src/ITKBridgeNumPy/test/Docker/test.sh
