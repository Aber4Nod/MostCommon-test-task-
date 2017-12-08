#!/bin/bash

./tests/fills/chrg.sh
for thr in `seq 1 10`
do
    cp ./tests/copies/* ./tests/tmp/
    ./tests/fills/eval.sh $thr
    ./tests/fills/chreslt.sh
    rm -f ./tests/tmp/*
    rm -f ./res/*
done
rm -f ./tests/copies/*
