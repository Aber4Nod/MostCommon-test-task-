#!/bin/bash

./tests/fills/rtests.sh
cp ./tests/copies/* ./tests/tmp/
./tests/fills/eval.sh 4
./tests/fills/chreslt.sh
rm -f ./tests/tmp/*
rm -f ./res/*
rm -f ./tests/copies/*
